#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct Node Node;

struct Node {
	char *key;
	Node *next;
};

typedef struct {
	Node **buckets;
	int size;
} HashSet;

static char *normalize(const char *email) {
	int len = (int)strlen(email);
	char *out = malloc(len + 1);
	int oi = 0;
	const char *p = email;
	int skip = 0;

	while (*p && *p != '@') {
		if (*p == '+') skip = 1;
		else if (!skip && *p != '.') out[oi++] = *p;
		p++;
	}
	while (*p) out[oi++] = *p++;

	out[oi] = '\0';
	return out;
}

static unsigned int hashStr(const char *s) {
	unsigned int r = 5381;
	while (*s) r = ((r << 5) + r) + (unsigned char)(*s++);
	return r % MAX_SIZE;
}

static HashSet *initHashSet(void) {
	HashSet *set = calloc(1, sizeof(HashSet));
	set->buckets = calloc(MAX_SIZE, sizeof(Node *));
	set->size = 0;
	return set;
}

static int addKey(HashSet *set, char *key) {
	unsigned int i = hashStr(key);
	for (Node *p = set->buckets[i]; p; p = p->next) {
		if (strcmp(p->key, key) == 0) {
			free(key);
			return 0;
		}
	}
	Node *node = calloc(1, sizeof(Node));
	node->key = key;
	node->next = set->buckets[i];
	set->buckets[i] = node;
	set->size++;
	return 1;
}

static void freeHashSet(HashSet *set) {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node *p = set->buckets[i];
		while (p) {
			Node *nx = p->next;
			free(p->key);
			free(p);
			p = nx;
		}
	}
	free(set->buckets);
	free(set);
}

int numUniqueEmails(char **emails, int emailsSize) {
	HashSet *set = initHashSet();

	for (int i = 0; i < emailsSize; i++) {
		char *key = normalize(emails[i]);
		addKey(set, key);
	}

	int result = set->size;
	freeHashSet(set);
	return result;
}
