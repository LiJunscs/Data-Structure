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
	//��ʼ��һ������
	struct heap* H = (struct heap*)malloc(sizeof(struct heap*));
	H->nums = (int*)malloc(sizeof(int) * maxsize);
	H->size = 0;
	H->maxSize = maxsize;
	//�����С��0λ����Ϊһ���ڱ�
	H->nums[0] = MAXNUM;
	return H;
}
//����в���Ԫ��
void insertHeap(struct heap* H,int item) {
	//������Ԫ�ط����ڶѵ�ĩβ��Ȼ��������ϵ�����������ڵ�С�������򸸽ڵ�������������ȥ��
	int i;
	i = ++H->size;
	for (; H->nums[i / 2] < item && i>1; i /= 2)
		H->nums[i] = H->nums[i / 2];
	H->nums[i] = item;
}
//ɾ������Ԫ�أ����ظ�Ԫ��
int deleteHeap(struct heap* H) {
	//ɾ���ѵĵ�һ��Ԫ�أ�������Ѷ�Ԫ�أ������һ��Ԫ���õ��Ѷ���Ȼ�����µ�����
	int parent, child, tmp, maxItem;
	//����Ѷ�Ԫ��
	maxItem = H->nums[1];
	//ȡ���ѵ����һ��Ԫ��
	tmp = H->nums[H->size--];
	//�����һ��Ԫ�طŵ��Ѷ���Ȼ��ѡ�����Ҷ����д��һ��������λ�ã���������
	for (parent = 1; parent * 2 <= H->size; parent = child) {
		child = parent * 2;
		//ѡ�����Ҷ����д��һ��
		if (child < H->size && H->nums[child] < H->nums[child + 1])
			child++;
		//������Ҷ��Ӷ��ȸ��״����ü�������
		if (tmp > H->nums[child])
			break;
		else H->nums[parent] = H->nums[child];
	}
	H->nums[parent] = tmp;
	return maxItem;
}
//�����������齨�ѣ��������һ����Ҷ�ӽڵ㿪ʼ��������
struct heap* create_maxHeap(int* nums, int numsSize) {
	int i = numsSize / 2;//���������һ����Ҷ�ӽڵ�
	int parent, child, tmp;
	struct heap* H;
	for (i = numsSize / 2; i >= 1; i--) {
		//��ɾ���Ѷ�Ԫ�صķ�ʽ�Ӻ���ǰ�����ε�����������
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