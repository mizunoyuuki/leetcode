/* サイズKのMin-Heap(優先度付きキュー) */
/* 自分の実装は、二分探索木っていう名前だったらしい */

/* この優先度付きキューが最もオーソドックスな解法らしい 
 * アイデア: 「k個の最大値だけ保持するヒープ」を維持する。ヒープの先頭が常にk番目の最大値になる。
 * */

/* 
 * そもそもヒープって何？？mallocで使う場所のこと？？
 *
 * Min-Heap・優先度付きキューの関係
 *
 * 優先度付きキュー = 概念
 * Min-Heap         = 実装方法
 *
 * ヒープとは
 * 完全二分木(葉以外には必ず子が二つある木)に、親子間のルールを加えたもの
 *
 * ルールが二種類ある。
 * Max-Heap: 親は必ず子より大きい(または等しい)
 *
 * Min-Heap
 * 親は必ず子より小さい
 *
 *
 * 今回の実装は、k番目に大きな値がrootにあるような、Min-Heapを実装することで、データの挿入は、O(log n)、抽出はO(1)ってことになる。
 * */

//てなことで実装開始。
//
// 今回は学習がてらポインタを繋げた完全二分木をちゃんと実装する。

typedef struct PqNode PqNode;
typedef struct KthLargest KthLargest;

struct PqNode {
	int val;
	PqNode *parent;
	PqNode *left;
	PqNode *right;
};

struct KthLargest{
	PqNode *root;
	int k;
	int size;
};

KthLargest *init_priority_queue(int k){
	KthLargest *kl = calloc(1, sizeof(KthLargest));
	kl->size = 0;
	kl->k = k;

	return kl;
}



PqNode *push_node(KthLargest *kl, int val){
	int pos = kl->size + 1;

	// posのビット数を数える
	int depth = 0;
	int tmp = pos;
	while (tmp > 0) {
		depth++;
		tmp >>= 1;
	}

	if (kl->size == 0) {
		PqNode *node = calloc(1, sizeof(PqNode));
          	node->val = val;
          	kl->root = node;
          	kl->size += 1;
          	return node;
        }

	PqNode *parent = kl->root;

	for(int i=depth-2; i>=1; i--){
		if ((pos >> i) & 1)
			parent = parent->right;
		else
			parent = parent->left;
	}

	PqNode *node = calloc(1, sizeof(PqNode));
	node->val = val;
	node->parent = parent;

	if ((pos >> 0) & 1)
		parent->right = node;
	else
		parent->left = node;

	kl->size += 1;

	return node;
}

void shift_up(PqNode *node){
	while (node->parent != NULL){
		if (node->parent->val <= node->val) break;

		int tmp = node->parent->val;
		node->parent->val = node->val;
		node->val = tmp;

		node = node->parent;
	}
	return;
}

void shift_down(PqNode *node){
	while(1){
		PqNode *smallest = node;

		if(node->left != NULL && node->left->val < smallest->val)
			smallest = node->left;
		if(node->right != NULL && node->right->val < smallest->val)
			smallest = node->right;

		if (smallest == node) break;

		int tmp = node->val;
		node->val = smallest->val;
		smallest->val = tmp;

		node = smallest;
	}
}

int kthLargestAdd(KthLargest* obj, int val) {
	if (obj->size < obj->k){
		PqNode *insert_node = push_node(obj, val);
		shift_up(insert_node);
	} else {
		if (obj->root->val > val) return obj->root->val;

		obj->root->val = val;
		shift_down(obj->root);
	}

	return obj->root->val;
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
	KthLargest *kl = init_priority_queue(k);

	for (int i=0; i<numsSize; i++){
		kthLargestAdd(kl, nums[i]);
	}

	return kl;
}

void kthLargestFree(KthLargest* obj) {
    
}


