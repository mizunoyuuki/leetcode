int subarraySum(int *nums, int numsSize, int k){
	int i = 0;
	int end;
	int sum;
	while (i < numsSize){
		sum = 0;
		end = i;
		while(sum <= k && end < numsSize){
			sum += nums[end];
			if (sum == k) return end - i + 1;
			end++;
		}
		i++;
	}

	return numsSize;
}
