typedef struct Element {
	int index;
	int number;
} Element;

int compare(const void *a, const void *b){
	Element *ea = (Element *)a;
	Element *eb = (Element *)b;

	return ea->number - eb->number;  // 昇順ソート
}

Element* binsearch(Element *e, int left_index, int right_index, int target){
	while (left_index <= right_index){
		int middle = (left_index + right_index + 1) / 2;
		if (e[middle].number == target) return &e[middle];

		e[middle].number  < target ? (left_index = middle + 1) :(right_index = middle - 1);
	}

	return NULL;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
	Element* elems = calloc(numsSize, sizeof(Element));
	int *result = malloc(2 * sizeof(int));

	// ソートしても元のインデックスが崩れないように構造体でくくる
	for (int i = 0; i < numsSize; i++){
		(*(elems + i)).index = i;
		(*(elems + i)).number = nums[i];
	}

	// Cの標準ライブラリにqsortがある。
	//   配列    要素数    1要素のサイズ    比較関数
	qsort(elems, numsSize, sizeof(Element), compare);

	int left = numsSize - 1;
	for (int i = 0; i < numsSize; i++){
		// 欲しい数字
		int t_number = target - elems[i].number;

		Element *r = binsearch(elems, i+1, left, t_number);
		if (r){
			result[0] = elems[i].index;
			result[1] = r->index;

			*returnSize = 2;
			return result;
		}
	}

	*returnSize = 0;
	return NULL;
}
