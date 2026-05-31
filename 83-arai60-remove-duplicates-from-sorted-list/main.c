/* Remove Duplicates from Sorted List */

typedef struct Node Node;
typedef struct HashMap HashMap;
typedef struct ListNode ListNode;

struct Node {
	int val;
	Node *next;
};

struct HashMap {
	Node **buckets;
	int size;
};

unsigned int hash(int val){
	return ((unsigned int )val)  % 300;
}

bool search_hashmap(HashMap *hm, unsigned int h_index, int val){
	Node *node = hm->buckets[h_index];

	while(node){
		if (node->val == val){
			return true;
		}

		node = node->next;
	}
	return false;
}

void insert_hashmap(HashMap *hm, unsigned int h_index, int val){
	Node *node = hm->buckets[h_index];

	Node *i_node = calloc(1, sizeof(Node));
	i_node->val = val;

	i_node->next = node;
	hm->buckets[h_index] = i_node;
}


struct ListNode* deleteDuplicates(struct ListNode *head){
	if (head == NULL) return false;

	ListNode *cur = head;

	/* HashMapの初期化*/
	Node **buckets = calloc(300, sizeof(Node*));
	HashMap *hashmap = calloc(1, sizeof(HashMap));
	hashmap->buckets = buckets;
	hashmap->size = 300;

	/* 初めのvalのノードは起点になるため入れておく*/
	unsigned int h_index = hash(cur->val);
	insert_hashmap(hashmap, h_index,cur->val);

	while(cur->next){
		unsigned int h_index = hash(cur->next->val);

		bool is_exist = search_hashmap(hashmap, h_index, cur->next->val);

		if (is_exist){
			cur->next = cur->next->next;
			continue;
		}

		insert_hashmap(hashmap, h_index, cur->next->val);
		cur = cur->next;
	}

	return head;
}
