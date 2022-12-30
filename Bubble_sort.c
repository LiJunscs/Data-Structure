void bubble_sort(int* nums, int numsSize) {
	int i, j, flag = 1;
	for (i = 0; i < numsSize && flag == 1; i++) {
		flag = 0;
		for (j = 0; j < numsSize - 1 - i; j++) {
			if (nums[j] > nums[j + 1]) {
				flag = 1;
				int tmp = nums[j + 1];
				nums[j + 1] = nums[j];
				nums[j] = tmp;
			}
		}
	}
}