
typedef struct Node Node;

struct Node {
	int val;
	int index1;
	int index2;
};

typedef struct MinHeap {
	Node **tree;
	int k;
	int size;
}MinHeap;

void shift_up(MinHeap *mh){
}

void get_smallest(int *nums1, int *nums2, int nums1Size, int nums2Size, int i, int j, int *inp, int *jnp){
}

void insert(MinHeap *mh, int *nums1, int *nums2, int i, int j){
}

MinHeap *init_minheap(int k){
	MinHeap *mh = calloc(1, sizeof(MinHeap));
	mh->tree = calloc(k, sizeof(Node*));
	mh->k = k;
	mh->size = 0;

	return mh;
}

int **kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSize){
	int i=0;
	int j=0;
	int inp;
	int jnp;

	MinHeap *mh = init_minheap(k);

	for (int c=0; c < k; c++){
		get_smallest(nums1, nums2, nums1Size, nums2Size, i, j, &inp, &jnp);
		insert(mh, nums1, nums2, inp, jnp);
		shift_up(mh);

		i = inp;
		j = jnp;
	}
}
