typedef struct HashMap HashMap;
typedef struct Node Node;

struct Node {
	int n;
	int count;
	Node *next;
};

struct HashMap {
	Node **buckets;
	int sum;
    int numsSize;
    int k;
};

HashMap *initHashMap(int *nums, int numsSize){
	HashMap *hm = malloc(sizeof(HashMap));
	hm->buckets = calloc(numsSize * 2, sizeof(Node*));
    hm->sum = 0;
    hm->numsSize = numsSize;

	Node *node = calloc(1, sizeof(Node));
	node->n = 0;
	node->count = 1;

	hm->buckets[0] = node;

	return hm;
}

unsigned int hash(int sum, int numsSize){
	return ((unsigned int)sum * 311212) % (unsigned int)numsSize;
}

int search(HashMap *hm, int k){
	int target = hm->sum - k;

	unsigned int i = hash(target, hm->numsSize);

	Node *node = hm->buckets[i];
	while (node){
		if (node->n == target) return node->count;

		node = node->next;
	}

	return 0;
}

void insert(HashMap *hm, int s){
	unsigned int i = hash(s, hm->numsSize);

	Node *n = hm->buckets[i];
	while (n){
		if (n->n == s){
			n->count += 1;
			return;
		}
		n = n->next;
	}

	Node *node = calloc(1, sizeof(Node));
	node->n = s;
	node->count = 1;
	node->next = hm->buckets[i];
	hm->buckets[i] = node;
}

int subarraySum(int *nums, int numsSize, int k){
	HashMap *hm = initHashMap(nums, numsSize);
	int count = 0;

	for (int i=0; i < numsSize; i++){
		hm->sum += nums[i];
		count += search(hm, k);
		insert(hm, hm->sum);
	}

	return count;
}
