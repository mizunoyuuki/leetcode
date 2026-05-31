/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *result = malloc(2 * sizeof(int));
    for (int i = 0; i < numsSize; i++){
        for (int j = i + 1; j < numsSize; j++){
            if (target == *(nums + i) + *(nums + j)){
                result[0] = i;
                result[1] = j;

                *returnSize = 2;
                return result;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}



/*
 * この実装だとO(n^2)の時間計算量である。
 * ちなみに空間計算量とは、データが増えたらどれだけメモリを使うのか。という指標
 *
 * HashMapを使うことで計算量を減らすことができる
 *
 * target = a[i] + a[j]
 * target - a[i] = a[j]
 *
 * a[j]の値があるかどうかをHashで持っておくことで高速化できる。
 * Cだと簡易なHashMapは配列で実装することができる。
 */

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
	int *result = malloc(2 * sizeof(int));
        int map[2 * 10000];
        memset(map, -1, sizeof(map));
        
        for (int i = 0; i < numsSize; i++){
            int sub = target - nums[i];
            if (map[10000 + sub] != -1) {
                result[0] = i;
                result[1] = map[10000 + sub];
                
                *returnSize = 2;
                return result;
            }
            map[10000 + nums[i]] = i;
        }
        *returnSize = 0;
        return NULL;
}

こんな感じで書くことでHashMapを配列で表現することができる。
ただこの書き方ではメモリのスタックに載せることができる量のHashMapしか作ることができない。

要は、このtwo-sumのような8Gのデカさになる配列とかだったら実装できない。

本格的なHashMapでは、
チェイン法などが必要になる。

それ以外にも、ソートしてから二分探索・といったやり方でも時間計算量を短縮することができる。

ただ、ハッシュマップは、メモリをある程度食うため、極端にメモリが制限されている場合はハッシュマップが選択できないこともある。
マイコンとか

また、最悪計算量が保証できない問題もある。

ハッシュマップには弱点があり、
通常は、O(1)で計算できるが、
ハッシュ衝突が起きると、
- "abc" => 3番
- "xyz" => 3番
最悪の場合: O(n)になる。

すでにソート済みのデータなら, わざわざハッシュマップを作らなくとも, 二分探索を行った方が早い


ソート*二分探索は、O(log n)の計算量となり、飛行機の制御とか、医療機器とか、原発のシステムとか、
「必ず最悪でも⭕️秒以内に終わる」ことが求められる環境では、ハッシュマップではなく ソート + 二分探索のO(log n)確定保証の方が安全になる

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

		e[middle].number  < target ? left_index = middle + 1 : right_index = middle - 1;
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
			result[1] = r.index;

			*returnSize = 2;
			return result;
		}
	}

	*returnSize = 0;
	return NULL;
}


