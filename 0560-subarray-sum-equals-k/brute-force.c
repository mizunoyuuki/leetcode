int subarraySum(int *nums, int numsSize, int k){
	int i = 0;
	int end;
	int sum;
    int count = 0;
	while (i < numsSize){
		sum = 0;
		end = i;
		while(end < numsSize){
			sum += nums[end];
			if (sum == k) count++;
			end++;
		}
		i++;
	}

	return count;
}
