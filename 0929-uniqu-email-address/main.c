# define MAX_SIZE 100

typedef struct HashMap HashMap;
typedef struct Node Node;

struct Node {
	char *email;
	Node *next_email;
	Node *next;
};

struct HashMap{
	HashMap **hash_maps;
	int size;
};


// local
// . と +の後ろを除外した長さを引数を戻り値に
// domainの開始位置を返す
char *strlenLocal(char *email, int *count){
	int count = 0;
	// local
	while (email && *email!='@'){
		if (*email == '+'){
			while (email && email != '@')
				email++;
		}
		if (*email == '.') continue;

		count++;
	}

	return ++email;
}

// domain
// '\0'を除外した長さを返す
int strlenDomain(char *domain){
	int count = 0;

	// domain
	while (domain){
		count++;
	}

	return count;
}

// localの.と+以降を除いた文字列をHash化

int hashLocal(char *email){
	int len;
	char *domain = strlenLocal(email, &len);

}

int hashDomain(char *domain){
}

// 2つのemailの. + を無視した一致確認
int cmpEmail(char *email1. char *email2){
	int len1;
	int len2;
	char *domain1 = strlenLocal(email1, &len1);
	char *domain2 = strlenLocal(email2, &len2);

	if (len1 != len2) return 0;

	return cmpDomain(domain1, domain2);
}

// domainの一致を確認
int cmpDomain(char *domain1, char *domain2){
	int len1 = strlenDomain(domain1);
	int len2 = strlenDomain(domain2);

	if (len1 != len2) return 0;

	while ((d1 = domain1) && (d2 = domain2)){
		if (*d1 != *d2) return 0;
	}

	return 1;
}

void insertEmail(HashMap *root_hash, char *email){
	char *tmp = email;
	int lhash_i = hashLocal(tmp);

	HashMap *domain_hash = insertDomain(root_hash->buckets[lhash_i]);

	int dhash_i = hashDomain(domain);

	domain_hashmap->buckets[dhash_i];
}

HashMap *initHashMap(){
	HashMap *hm = calloc(1, sizeof(HashMap));
	hm->size;
	hm->buckets = calloc(MAX_SIZE, sizeof(Node*));

	return hm;
}

int numUniqueEmails(char **emails, int emailsSize){
	HashMap *root_hash = initHashMap();

	for (int i = 0; i < emailsSize; i++){
		insertEmail(root_hash, email[i]);
	}

	return root_hash->size;
}
