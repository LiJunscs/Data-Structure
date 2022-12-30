void select_sort(int* nums, int numsSize) {
	int i, j;
	for (i = 0; i < numsSize; i++) {
		int max = i;
		for (j = i; j < numsSize - 1; j++) {
			if (nums[j] < nums[max])
				max = j;
		}
		int tmp = nums[max];
		nums[max] = nums[i];
		nums[i] = tmp;
	}
}