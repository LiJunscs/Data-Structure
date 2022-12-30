void match(int* nums, int* tmp, int start1, int end1, int start2, int end2) {
	int i = start1, j = start2, k = start1;
	while (i <= end1 && j <= end2) {
		if (nums[i] <= nums[j])
			tmp[k++] = nums[i++];
		else tmp[k++] = nums[j++];
	}
	while (i <= end1)
		tmp[k++] = nums[i++];
	while (j <= end2)
		tmp[k++] = nums[j++];
	for (i = start1; i <= end2; i++)
		nums[i] = tmp[i];
}
void merge(int* tmp, int* nums, int start, int end) {
	int mid = (start + end) / 2;
	if (start < end) {
		merge(tmp, nums, start, mid);
		merge(tmp, nums, mid + 1, end);
		match(nums, tmp, start, mid, mid + 1, end);
	}
}
void merge_sort(int* nums, int numsSize) {
	int* tmp = (int*)malloc(sizeof(int) * numsSize);
	int start = 0, end = numsSize - 1;
	merge(tmp, nums, start, end);
}
void print(int* nums, int numsSize) {
	for (int i = 0; i < numsSize; i++)
		printf("%d ", nums[i]);
	printf("\n");
}