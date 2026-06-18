#include<stdio.h>

void quick_sort(int *array, int left, int right){
	if (right <= left) return;

	int store = left;
	int pivot = array[right];

	for (int i = left; i < right; i++){
		if (array[i] < pivot){
			int tmp = array[i];
			array[i] = array[store];
			array[store] = tmp;
			store++;
		}
	}

	int tmp = array[store];
	array[store] = array[right];
	array[right] = tmp;

	quick_sort(array, left, store-1);
	quick_sort(array, store+1, right);

	return;
}

int main(){
	int data[10] = {10, 8, 1, 18, 129, 4, 12, 43, 111, 12};
	quick_sort(data, 0, 9);

	for (int i=0; i < 10; i++){
		printf("%d\t", data[i]);
	}

	printf("\n");

	return 0;
}
