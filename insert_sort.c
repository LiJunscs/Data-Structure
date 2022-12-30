void insert_sort(int* nums, int numsSize) {
	int i, j;
	for (i = 0; i < numsSize; i++) {
		int tmp = nums[i];
		for (j = i - 1; j > 0 && nums[j] < nums[j - 1]; j--)
			nums[j] = nums[j - 1];
		nums[j] = tmp;
	}
}