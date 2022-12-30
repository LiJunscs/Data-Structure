void quick_sort(int* nums, int numsSize) {
	int i = 0, j = numsSize - 1;
	int key = nums[i];
	while (i < j) {
		while (i < j && nums[j] >= key)
			j--;
		nums[i] = nums[j];
		while (i < j && nums[i] <= key)
			i++;
		nums[j] = nums[i];
	}
	nums[i] = key;
	if (numsSize > 0) {
		quick_sort(nums, i);
		quick_sort(&nums[i + 1], numsSize - i - 1);
	}
}