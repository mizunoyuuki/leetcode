#include <stdlib.h>

# define MAX_SIZE 1011

typedef struct HashMap HashMap;
typedef struct Result Result;
typedef struct Node Node;

struct Node {
	int val;
	Node *next;

	// only search member
	int visited;
};

struct HashMap {
	Node **buckets;
};

struct Result {
	int size;
	int arr[MAX_SIZE];
};

void push(Result *r, int i){
	r->arr[r->size] = i;
	r->size += 1;

	return;
}


int max(int i, int j){
	return i > j ? i : j;
}

HashMap *initHashMap(){
	HashMap *hm = malloc(sizeof(HashMap));
	hm->buckets = calloc(MAX_SIZE, sizeof(Node*));

	return hm;
}

unsigned int hash(int i){
	return ((unsigned int)i * 5183) % MAX_SIZE;
}

void insert(HashMap *hm, int j){
	unsigned int hashi = hash(j);
	// すでにハッシュ値がある場合
	Node *c_node = hm->buckets[hashi];
	if (c_node) {
		while (c_node){
			if (c_node->val == j) {
				break;
			}
			c_node = c_node->next;
		}
		Node *tmp = hm->buckets[hashi];
		Node *new_root = malloc(sizeof(Node));
		new_root->val = j;
		new_root->next = tmp;
		hm->buckets[hashi] = new_root;

	} else {
		Node *node = calloc(1, sizeof(Node));
		node->val = j;
		hm->buckets[hashi] = node;
	}
}

int search(HashMap *hm, int j){
	unsigned int hashi = hash(j);

	Node *c_node = hm->buckets[hashi];

	while(c_node){
		if (c_node->val == j && !c_node->visited){
			c_node->visited = 1;
		       	return 1;
		}
		c_node = c_node->next;
	}

	return 0;
}

int *intersection(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize){
	int max_size = max(nums1Size, nums2Size);
	HashMap *hm =  initHashMap();

	for (int i=0; i < nums1Size; i++){
		insert(hm, nums1[i]);
	}

	Result r;
	r.size = 0;

	for (int i=0; i < nums2Size; i++){
		if (search(hm, nums2[i])) push(&r, nums2[i]);
	}


	int *result = malloc(r.size * sizeof(int));
	for (int i=0; i < r.size; i++ ){
		result[i] = r.arr[i];
	}

	*returnSize = r.size;

	return result;
}
