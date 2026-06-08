typedef struct KthLargest KthLargest;
typedef struct PqNode PqNode;

struct KthLargest {
	PqNode *root;
	int k;
	int size;
};

struct PqNode {
	int val;
	PqNode *parent;
	PqNode *left;
	PqNode *right;
};

int kthLargestAdd(KthLargest* obj, int val);

KthLargest *init_priority_queue(int k){
	KthLargest *kl = calloc(1, sizeof(KthLargest));
	kl->size = 0;
	kl->k = k;

	return kl;
}

KthLargest *kthLargestCreate(int k, int* nums, int numsSize){
	KthLargest *kl = init_priority_queue(k);

	for(int i=0; i<numsSize; i++){
		kthLargestAdd(kl, nums[i]);
	}

	return kl;
}

PqNode *push_node(KthLargest *kl, int val){
	int pos = kl->size + 1;

	int depth = 0;
	int tmp = pos;
	while(tmp > 0){
		depth++;
		tmp >>= 1;
	}

	if(kl->size == 0){
		PqNode *node = calloc(1, sizeof(PqNode));
		node->val = val;
		kl->root = node;
		kl->size += 1;
		return node;
	}

	PqNode *parent = kl->root;

	for(int i = depth - 2; i >= 1; i--){
		if((pos >> i) & 1)
			parent = parent->right;
		else
			parent = parent->left;
	}

	PqNode *node = calloc(1, sizeof(PqNode));
	node->val = val;
	node->parent = parent;

	if((pos >> 0) & 1)
		parent->right = node;
	else
		parent->left = node;

	kl->size += 1;

	return node;
}

void shift_up(PqNode *node){
	while(node->parent && node->val < node->parent->val){
		int tmp = node->val;
		node->val = node->parent->val;
		node->parent->val = tmp;
		node = node->parent;
	}
}

void shift_down(PqNode *node){
	while(1){
		PqNode *smallest = node;

		if(node->left && node->left->val < smallest->val)
			smallest = node->left;
		if(node->right && node->right->val < smallest->val)
			smallest = node->right;

		if(smallest == node) break;

		int tmp = smallest->val;
		smallest->val = node->val;
		node->val = tmp;

		node = smallest;
	}
}

int kthLargestAdd(KthLargest* obj, int val){
	if(obj->size < obj->k){
		PqNode *node = push_node(obj, val);
		shift_up(node);
	} else {
		if(obj->root->val > val) return obj->root->val;
		obj->root->val = val;
		shift_down(obj->root);
	}

	return obj->root->val;
}

void kthLargestFree(KthLargest* obj){
}
