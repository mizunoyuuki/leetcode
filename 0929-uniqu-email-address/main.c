#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024

typedef struct Node Node;
typedef struct HashMap HashMap;

struct Node {
	char *email;       // 元 email へのポインタ(level1=local起点 / level2=domain起点)
	HashMap *child;    // level1 ノードのみ使用: domain 用のハッシュマップ
	Node *next;        // 同一バケット内のチェイン
};

struct HashMap {
	Node **buckets;
	int size;          // 格納済みノード数
};

/* ---------- 文字走査ヘルパ ---------- */

// local を正規化しつつ次の「有効な1文字」を返す。
// '.' は飛ばし、'+' / '@' / '\0' に達したら local の終端として '\0' を返す。
static char nextLocalChar(char **pp) {
	char *p = *pp;
	while (*p == '.') p++;                         // '.' は無視
	char c;
	if (*p == '\0' || *p == '@' || *p == '+')      // ここで local は終わり
		c = '\0';
	else
		c = *p++;
	*pp = p;
	return c;
}

// '@' の次(domain 先頭)を返す
char *strlenLocal(char *email) {
	char *p = email;
	while (*p && *p != '@') p++;
	return (*p == '@') ? p + 1 : p;
}

// domain の長さ('\0' を除く)
int strlenDomain(char *domain) {
	int count = 0;
	while (domain[count]) count++;
	return count;
}

/* ---------- ハッシュ関数(djb2) ---------- */

// 正規化した local をハッシュ化
unsigned int hashl(char *email) {
	unsigned int r = 5381;
	int skip = 0;
	for (char *p = email; *p && *p != '@'; p++) {
		if (*p == '+') skip = 1;
		else if (!skip && *p != '.')
			r = ((r << 5) + r) + (unsigned char)*p;   // r*33 + c
	}
	return r % MAX_SIZE;
}

// domain をハッシュ化
unsigned int hashd(char *domain) {
	unsigned int r = 5381;
	for (char *p = domain; *p; p++)
		r = ((r << 5) + r) + (unsigned char)*p;
	return r % MAX_SIZE;
}

/* ---------- 比較 ---------- */

// 2つの email の正規化 local が一致するか
int cmpEmail(char *email1, char *email2) {
	char *a = email1, *b = email2;
	while (1) {
		char ca = nextLocalChar(&a);
		char cb = nextLocalChar(&b);
		if (ca != cb) return 0;
		if (ca == '\0') return 1;
	}
}

// domain の一致確認
int cmpDomain(char *domain1, char *domain2) {
	return strcmp(domain1, domain2) == 0;
}

/* ---------- マップ操作 ---------- */

HashMap *initHashMap() {
	HashMap *hm = calloc(1, sizeof(HashMap));
	hm->buckets = calloc(MAX_SIZE, sizeof(Node *));
	hm->size = 0;
	return hm;
}

// domain を level2 マップへ挿入。新規なら1、既存なら0。
int insertDomain(HashMap *hash, char *domain) {
	unsigned int i = hashd(domain);
	for (Node *p = hash->buckets[i]; p; p = p->next)
		if (cmpDomain(p->email, domain)) return 0;   // 既出

	Node *node = calloc(1, sizeof(Node));
	node->email = domain;
	node->next = hash->buckets[i];
	hash->buckets[i] = node;
	hash->size++;
	return 1;
}

// email を二段ハッシュへ挿入。新規ユニークなら1。
int insertEmail(HashMap *root_hash, char *email) {
	unsigned int li = hashl(email);

	// 同じ正規化 local の level1 ノードを探す
	Node *ln = NULL;
	for (Node *p = root_hash->buckets[li]; p; p = p->next) {
		if (cmpEmail(p->email, email)) { ln = p; break; }
	}

	// 無ければ作成し、子(domain マップ)を持たせる
	if (!ln) {
		ln = calloc(1, sizeof(Node));
		ln->email = email;
		ln->child = initHashMap();
		ln->next = root_hash->buckets[li];
		root_hash->buckets[li] = ln;
	}

	char *domain = strlenLocal(email);
	return insertDomain(ln->child, domain);
}

void freeHashMap(HashMap *hash) {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node *p = hash->buckets[i];
		while (p) {
			Node *nx = p->next;
			if (p->child) freeHashMap(p->child);
			free(p);
			p = nx;
		}
	}
	free(hash->buckets);
	free(hash);
}

int numUniqueEmails(char **emails, int emailsSize) {
	HashMap *root_hash = initHashMap();
	int count = 0;

	for (int i = 0; i < emailsSize; i++) {
		int is_new = insertEmail(root_hash, emails[i]);
		if (is_new) count++;
	}

	freeHashMap(root_hash);
	return count;
}
