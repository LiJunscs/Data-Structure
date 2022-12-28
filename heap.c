#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNUM 10000
#define MAXSIZE 1000
struct heap {
	int* nums;
	int size;
	int maxSize;
};
struct heap* init_maxHeap(int);
void insertHeap(struct heap*, int);
int deleteHeap(struct heap*);
struct heap* create_maxHeap(int*, int);
void freeHeap(struct heap*);
struct heap* init_maxHeap(int maxsize) {
	//初始化一个最大堆
	struct heap* H = (struct heap*)malloc(sizeof(struct heap*));
	H->nums = (int*)malloc(sizeof(int) * maxsize);
	H->size = 0;
	H->maxSize = maxsize;
	//数组的小标0位置作为一个哨兵
	H->nums[0] = MAXNUM;
	return H;
}
//向堆中插入元素
void insertHeap(struct heap* H,int item) {
	//将插入元素放置在堆的末尾，然后逐层往上调整，如果父节点小于自身，则父节点下来，自身上去，
	int i;
	i = ++H->size;
	for (; H->nums[i / 2] < item && i>1; i /= 2)
		H->nums[i] = H->nums[i / 2];
	H->nums[i] = item;
}
//删除堆中元素，返回该元素
int deleteHeap(struct heap* H) {
	//删除堆的第一个元素，即保存堆顶元素，将最后一个元素拿到堆顶，然后重新调整堆
	int parent, child, tmp, maxItem;
	//保存堆顶元素
	maxItem = H->nums[1];
	//取出堆的最后一个元素
	tmp = H->nums[H->size--];
	//将最后一个元素放到堆顶，然后选择左右儿子中大的一个，交换位置，继续调整
	for (parent = 1; parent * 2 <= H->size; parent = child) {
		child = parent * 2;
		//选择左右儿子中大的一个
		if (child < H->size && H->nums[child] < H->nums[child + 1])
			child++;
		//如果左右儿子都比父亲大，则不用继续调整
		if (tmp > H->nums[child])
			break;
		else H->nums[parent] = H->nums[child];
	}
	H->nums[parent] = tmp;
	return maxItem;
}
//根据已有数组建堆，即从最后一个非叶子节点开始，调整堆
struct heap* create_maxHeap(int* nums, int numsSize) {
	int i = numsSize / 2;//数组中最后一个非叶子节点
	int parent, child, tmp;
	struct heap* H;
	for (i = numsSize / 2; i >= 1; i--) {
		//以删除堆顶元素的方式从后往前，依次调整出整个堆
		tmp = nums[i];
		for (parent = i; parent * 2 <= numsSize; parent = child) {
			child = parent * 2;
			if (child < numsSize-1 && nums[child] < nums[child + 1])
				child++;
			if (tmp > nums[child])
				break;
			else nums[parent] = nums[child];
		}
		nums[parent] = tmp;
	}
	H = init_maxHeap(MAXSIZE);
	memcpy(H->nums, nums, sizeof(int) * numsSize);
	H->size = numsSize - 1;
	return H;
}
void freeHeap(struct heap* H) {
	free(H->nums);
	free(H);
}