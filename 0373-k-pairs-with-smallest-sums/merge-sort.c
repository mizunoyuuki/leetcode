# include <stdio.h>
# include <stdlib.h>

void mergeSort(int *arr, int *tmp, int left, int right){
	if (left >= right) return;

	int middle = (left + right)/2;

	mergeSort(arr, tmp, left, middle);
	mergeSort(arr, tmp, middle+1, right);

	// if 8, 9で呼び出された場合
	// left 8, right 9で、
	// mergeSort(arr, 9, 9);
	// mergeSort(arr, 8, 8);
	// が呼び出されて止まって戻ってくる。その後の処理
	// (middle+1, right), (left, middle)はソート済みという認識でスタート

	int insert_position = left;
	int current_left = left;
	int current_right = middle+1;

	while(current_left <= middle && current_right <= right) {
		if(arr[current_left] > arr[current_right]){
			tmp[insert_position++] = arr[current_right++];
		} else {
			tmp[insert_position++] = arr[current_left++];
		}
	}

	while (current_left <= middle) tmp[insert_position++] = arr[current_left++];
	while (current_right <= right) tmp[insert_position++] = arr[current_right++];

	for (int i = left; i <= right; i++ ){
		arr[i] = tmp[i];
	}

	return;
}


int main(){
	int arr[15] = {
		10, 3, 0, 12, 111, 294, 1, 8, 23, 99,
		22, -1, 192, -12, 124
	};

	int *mtmp = malloc(sizeof(arr));

	mergeSort(arr, mtmp, 0, (sizeof(arr)/sizeof(arr[0]-1)));

	for (int i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++){
		printf("%d\n", arr[i]);
	}

	return 0;
}