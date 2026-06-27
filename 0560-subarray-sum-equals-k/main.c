// 累積和・メモ化あたりの理解がしたい
typedef struct HashMap HashMap;

struct HashMap {
	int *buckets;
};

HashMap *initHashMap(int *nums, int numsSize){
	int sum = 0;
	for (int i = 0; i < numsSize; i++){
		
	}
}

int subarraySum(int *nums, int numsSize, int k){
	HashMap *hm = initHashMap(nums, numsSize);
}
