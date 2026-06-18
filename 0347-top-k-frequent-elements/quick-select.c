# define MAX_SIZE 20001

typedef struct Node {
	int val;
	int count;
} Node;

void quickselect(Node **array, int target, int left, int right){
	if (left >= right) return;

	Node *pivot = array[right];
	int pivot_count = pivot->count;

	int store = left;
	for (int i = left; i < right; i++){
		if (array[i]->count < pivot_count){
			Node *tmp = array[i];
			array[i] = array[store];
			array[store] = tmp;
			store++;
		}
	}

	Node *tmp = array[store];
	array[store] = pivot;
	array[right] = tmp;

	if (store == target) return;

	if (store < target){
		quickselect(array, target, store+1, right);
	} else {
		quickselect(array, target, left, store - 1);
	}
}


int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
	int freq[MAX_SIZE] = {0};

	for (int i = 0; i < numsSize; i++){
		freq[nums[i] + 10000] += 1;
	}

	int size = 0;
	Node *array[numsSize];

	// arraynにsizeがsize, Nodeのアドレスを格納する配列を作成。これをquickselectする。
	for(int i = 0; i < MAX_SIZE; i++){
		if (freq[i] != 0) {
			Node *node = calloc(1, sizeof(Node));
			node->val = i - 10000;
			node->count = freq[i];
			array[size++] = node;
		}
	}

	quickselect(array, size - k, 0, size - 1);

	int *result = calloc(k, sizeof(int));

	int j = 0;

	for(int i = size - k; i < size; i++){
		result[j++] = array[i]->val;
	}
	
	*returnSize = k;
	return result;
}

