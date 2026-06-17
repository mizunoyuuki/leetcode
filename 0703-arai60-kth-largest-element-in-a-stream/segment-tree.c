# include<stdlib.h>
# include<stdio.h>

# define MAX 4 *32768

typedef struct SegmentTree SegmentTree;
struct SegmentTree {
	int tree[MAX];
};

// valをセグメント木に追加する
void update(SegmentTree *segt, int val, int start, int end, int index){
	int middle = (start + end)/2;
	if (middle != start || middle != end){
		val > middle ? update(segt, val, middle+1, end, 2*index+1) : update(segt, val, start, middle, 2*index);
	}

	segt->tree[index] += 1;

	return;
}

// k番目の値を返す
int search(SegmentTree *segt, int k, int start, int end, int index){
	if (start == end) return start;

	int middle = (start + end)/2;
	if (segt->tree[2*index+1] >= k){
		return search(segt, k, middle+1, end, 2*index+1);
	} else {
		return search(segt, k - segt->tree[2*index+1], start, middle, 2*index);
	}
}

int nums[] = {
      10000, -10000, 5000, -5000, 1, -1,
      7500, -7500, 3333, -3333, 9999, -9999,
      2500, -2500, 6000, -6000, 8888, -8888,
      100, -100, 4567, -4567, 7777, -7777,
      0, 1000, -1000, 9000, -9000, 50
};


SegmentTree *init_segment_tree(){
	SegmentTree *st = calloc(1, sizeof(SegmentTree));

	return st;
}

int main(){
	SegmentTree *st = init_segment_tree();

	int numsSize = sizeof(nums) / sizeof(nums[0]);

	for (int i = 0; i < numsSize; i++){
		update(st, nums[i] + 10000, 0, 20000, 1);
	}

	int result = search(st, 10, 0, 20000, 1);

	printf("%d\n", result - 10000);
	return result - 10000;
}

