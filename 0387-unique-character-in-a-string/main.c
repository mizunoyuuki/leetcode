typedef struct HashMap HashMap;
struct HashMap {
	int *buckets;
};

HashMap *initHashMap(){
	HashMap *hm = calloc(1, sizeof(HashMap));
	hm->buckets = calloc(30, sizeof(int));

	return hm;
}

void insert(HashMap *hm, char *c){
	int i = *c - 'a';
	hm->buckets[i]++;

	return;
}

int search(HashMap *hm, char *c){
	int i = *c - 'a';
	if (hm->buckets[i] == 1) return 1;

	return 0;
}

int firstUniqChar(char *s){
	HashMap *hm = initHashMap();
	char *tmp = s;

	while (*tmp){
		insert(hm, tmp);
		tmp++;
	}

	int count = 0;
	while(*s){
		if (search(hm, s)) return count;
		count++;
		s++;
	}

	return -1;
}
