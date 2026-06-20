typedef struct TwoSum {
	int val;
	// 何と何を足した結果なのか
	int index1;
	int index2;
} TwoSum;

void quickselect(TwoSum **arr, int target, int left, int right){
	if (left >= right || target >= right) return;
	int pivot = right;

	int store = left;
	for (int i = left; i < right; i++){
		if (arr[pivot]->val > arr[i]->val){
			TwoSum *tmp = arr[i];
			arr[i] = arr[store];
			arr[store] = tmp;
			store++;
		}
	}

	TwoSum *tmp = arr[store];
	arr[store] = arr[pivot];
	arr[pivot] = tmp;

	  if (target == store) return;
	  else if (target > store) quickselect(arr, target, store + 1, right);
	  else                     quickselect(arr, target, left, store - 1);
}


int **kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSize){
	int MAX = nums1Size * nums2Size;

	TwoSum **sum = calloc(MAX, sizeof(TwoSum*));

	// two_sumの結果を格納
	int p = 0;
	for(int i = 0; i < nums1Size; i++){
		int nums_i = nums1[i];
		for (int j = 0; j < nums2Size; j++){
			TwoSum *two_sum = calloc(1, sizeof(TwoSum));
			two_sum->val = nums_i + nums2[j];
			two_sum->index1 = i;
			two_sum->index2 = j;
			sum[p++] = two_sum;
		}
	}

	// quick_selectでやるか
	quickselect(sum, k-1, 0, MAX-1);

	int size = MAX < k ? MAX : k;
	*returnSize = size;
	*returnColumnSize = malloc(size * sizeof(int));
	for (int i=0; i < size; i++){
		(*returnColumnSize)[i] = 2;
	}

	int **result = calloc(size, sizeof(int*));
	for (int i = 0; i < size; i++){
		int *tmp = calloc(2, sizeof(int));
		tmp[0] = nums1[sum[i]->index1];
		tmp[1] = nums2[sum[i]->index2];
		result[i] = tmp;
	}

	return result;
}
