# define MAX 20001

# include<stdlib.h>

// MinHeapの管理元構造体
typedef struct MinHeap MinHeap;
typedef struct Node Node;

struct Node {
	int val;
	int count;
};

struct MinHeap {
	// ポインタの配列
	Node **tree;
	int k;
	int size;
};

// MinHeapの初期化・構造体の生成
MinHeap *init_min_heap(int k){
	MinHeap *mh = calloc(1, sizeof(MinHeap));
	mh->k = k;
	mh->size = 0;
	mh->tree = calloc(k, sizeof(Node*));

	return mh;
}

void shift_up(MinHeap *mh){
	if (mh->size == 0) return;

	int current_index = mh->size;
	while(current_index != 0){
		int parent_index = (current_index % 2 == 1) ? (current_index)/2 : (current_index)/2 - 1;

		if (mh->tree[parent_index]->count <= mh->tree[current_index]->count) break;

		Node *tmp = mh->tree[parent_index];
		mh->tree[parent_index] = mh->tree[current_index];
		mh->tree[current_index] = tmp;
			
		current_index = parent_index;
	}
}

void shift_down(MinHeap *mh){
	int current = 1;

	int smallest_index;

	while(2*current <= mh->size) {
		// 左の子ノードのcountがcurrentより小さい場合
		smallest_index = current-1;

		if (mh->tree[smallest_index]->count > mh->tree[2*current-1]->count){
			smallest_index = 2*current - 1;
		}

		if ( (mh->size > 2*current) && (mh->tree[smallest_index]->count > mh->tree[2*current]->count)){
			smallest_index = 2*current;
		}

		if (smallest_index == current - 1) break;

		Node *current_node = mh->tree[current-1];
		mh->tree[current-1] = mh->tree[smallest_index];
		mh->tree[smallest_index] = current_node;

		current = smallest_index + 1;
	}
}

void add_min_heap(MinHeap *mh, int val, int count){
	if (mh->size < mh->k){
		Node *node = calloc(1, sizeof(Node));
		node->val = val;
		node->count = count;

		mh->tree[mh->size] = node;

		// 一番したの左に入れて、MinHeapを更新する
		shift_up(mh);

		mh->size += 1;
		return;
	}

	if (mh->tree[0]->count > count) return;

	mh->tree[0]->val = val;
	mh->tree[0]->count = count;

	shift_down(mh);

	return;
}


int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
	int *freq = calloc(MAX, sizeof(int));

	// 数の出現回数を配列でカウント
	for (int i = 0; i < numsSize; i++){
		freq[nums[i] + 10000] += 1;
	}

	MinHeap *mh = init_min_heap(k);
	
	for (int i = 0; i < MAX; i++){
		if (freq[i] > 0){
			add_min_heap(mh, i - 10000, freq[i]);
		}
	}
	int *result = calloc(k, sizeof(int));

	for(int i=0; i < mh->size; i++){
		result[i] = mh->tree[i]->val;
	}

	*returnSize = mh->size;

	return result;
}
