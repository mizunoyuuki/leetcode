# include<stdlib.h>
# include<stdio.h>

typedef struct MinHeap MinHeap;
typedef struct Node Node;

struct Node {
	int val;
	int index1;
	int index2;
};

struct MinHeap {
	Node *tree;   // Node** → Node*（実体の連続配列）
	int size;
};

int min(int k, int n){
	return k > n ? n : k;
}

MinHeap *initMinHeap(int *nums1, int *nums2, int k, int nums1Size){
	MinHeap *mh = calloc(1, sizeof(MinHeap));
	int m = min(k, nums1Size);

	mh->size = m;
	mh->tree = malloc(m * sizeof(Node));   // ★1回だけ確保（calloc 1万回 → これ1回）

	for (int i = 0; i < m; i++){
		mh->tree[i].val    = nums1[i] + nums2[0];   // Node生成せず直接代入
		mh->tree[i].index1 = i;
		mh->tree[i].index2 = 0;
	}

	return mh;
}

Node pop(MinHeap *mh){      // Node* → Node（値で返す。reheapifyで上書きされても安全）
	return mh->tree[0];
}

// こんな感じ完
void shift_down(MinHeap *mh){
	int based1_index = 1;

	while (2 * based1_index <= mh->size){
		int smallest_index = based1_index;

		if (2 * based1_index <= mh->size){
			smallest_index = mh->tree[smallest_index - 1].val < mh->tree[2 * based1_index - 1].val ? smallest_index : 2 * based1_index;
		}

		if (2 * based1_index + 1 <= mh->size){
			smallest_index = mh->tree[smallest_index - 1].val < mh->tree[2 * based1_index].val ? smallest_index : 2 * based1_index + 1;
		}

		if (smallest_index == based1_index) break;

		Node tmp = mh->tree[based1_index - 1];          // 値のswap（int3個のコピー）
		mh->tree[based1_index - 1] = mh->tree[smallest_index - 1];
		mh->tree[smallest_index - 1] = tmp;

		based1_index = smallest_index;
	}
}

void shift_up(MinHeap *mh){
	int based1_index = mh->size;

	while(based1_index > 1){
		if (mh->tree[based1_index - 1].val >= mh->tree[(based1_index/2) - 1].val) break;

		Node tmp = mh->tree[(based1_index/2) - 1];
		mh->tree[(based1_index/2) - 1] = mh->tree[based1_index - 1];
		mh->tree[based1_index - 1] = tmp;

		based1_index = based1_index/2;
	}

	return;
}

void push(MinHeap *mh, int *nums1, int *nums2, int index1, int index2 ){
	mh->tree[mh->size].val    = nums1[index1] + nums2[index2];   // 確保せず代入
	mh->tree[mh->size].index1 = index1;
	mh->tree[mh->size].index2 = index2;
	mh->size += 1;

	return;
}

void changeRootHeapify(MinHeap *mh){
	mh->tree[0] = mh->tree[mh->size - 1];   // 末尾を根へ（値コピー）。NULL代入は不要
	mh->size -= 1;

	shift_down(mh);

	return;
}

int **kSmallestPairs(int *nums1, int nums1Size, int *nums2, int nums2Size, int k, int *returnSize, int **returnColumnsSize){

	MinHeap *mh = initMinHeap(nums1, nums2, k, nums1Size);

	long total = (long)nums1Size * nums2Size;   // 片方を long にキャストしてから掛ける
	int size = k < total ? k : (int)total;

	int **result = calloc(size, sizeof(int*));

	for (int i = 0; i < size; i++){
		int *a = calloc(2, sizeof(int));
		result[i] = a;
	}

	*returnSize = size;

	*returnColumnsSize = malloc(size * sizeof(int)); // 各行の長さの配列

	for (int i = 0; i < size; i++){
		(*returnColumnsSize)[i] = 2;
	}

	for (int i = 0; i < *returnSize; i++) {
		Node poped = pop(mh);      // Node* → Node（値）
		// 結果を格納
		result[i][0] = nums1[poped.index1];
		result[i][1] = nums2[poped.index2];

		changeRootHeapify(mh);

		// pushしたりしなかったりラジバンダリー
		poped.index2 + 1 >= nums2Size ? (void)0 : push(mh, nums1, nums2, poped.index1, poped.index2 + 1);
		shift_up(mh);
	}

	free(mh->tree);   // 個別Nodeのmallocが無くなったので、まとめて解放
	free(mh);

	return result;
}
