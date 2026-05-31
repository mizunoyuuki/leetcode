typedef struct Node Node;
typedef struct HashMap HashMap;
typedef struct ListNode ListNode;

struct Node {
	unsigned long long addr;
	Node *next;
};

struct HashMap {
	Node **buckets;
	int size;
};

unsigned int hash(unsigned long long addr){
	return (unsigned int)(addr * 2412344135498ULL / 10000) % 10000;
}

Node* search_hashmap(HashMap *hm, unsigned int hm_index, unsigned long long addr){
	Node *node = hm->buckets[hm_index];
	while (node){
		if (node->addr == addr){
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void insert_hashmap(HashMap *hm, unsigned int h_index, unsigned long long addr){
	Node *node = calloc(1, sizeof(Node));
	node->addr = addr;
	node->next = hm->buckets[h_index];
	hm->buckets[h_index] = node;
}


ListNode* detectCycle(struct ListNode *head){
	Node **buckets = calloc(10000, sizeof(Node*));

	/* init_hashmap */
	HashMap hashmap;
	hashmap.buckets = buckets;
	hashmap.size = 10000;

	ListNode *cur = head;
	while (cur){
		unsigned long long addr = (unsigned long long)cur;
		unsigned int h_index = hash(addr);
		Node *node = search_hashmap(&hashmap, h_index, addr);

		if (node) return (ListNode*)node->addr;

		insert_hashmap(&hashmap, h_index, addr);

		cur = cur->next;
	}

	return NULL;
}
