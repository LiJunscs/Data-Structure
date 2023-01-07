#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
//求集合的幂集，回溯
void backtrack(int *nums, int numsSize, int **res, int *returnSize, int **returnColSizes, int *set, int setSize, int index)
{
    if (*returnSize == 0)
    {   //将空集加入答案
        res[0] = NULL;
        (*returnColSizes)[0] = 0;
        (*returnSize)++;
    }
    else
    {   //为当前记录的子集申请空间，并加入答案二维数组
        res[*returnSize] = (int *)malloc(sizeof(int *) * setSize);
        (*returnColSizes)[*returnSize] = setSize;
        //将当前记录的子集复制到申请的空间
        memcpy(res[*returnSize], set, sizeof(int) * setSize);
        (*returnSize)++;
    }
    //从指定位置开始，往后遍历，将遍历到的数加入子集中
    for (int i = index; i < numsSize; i++)
    {
        set[setSize++] = nums[i];
        //从当前位置的下一个位置进行回溯
        backtrack(nums, numsSize, res, returnSize, returnColSizes, set, setSize, i + 1);
        //回溯结束，下标恢复
        setSize--;
    }
}
//int* returnSize为返回的二维数组的行数的指针，int** returnColumnSize为(int* returnColumnSize),存储每一个子集大小的数组的指针
int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    //为答案二维数组申请空间，并为存储子集大小的数组申请空间
    int len = pow(2, numsSize), index = 0, setSize = 0;
    int **res = (int **)malloc(sizeof(int *) * len);
    //申请一个子集数组，用来记录某个时刻的子集
    int *set = (int *)malloc(sizeof(int) * numsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * len);
    *returnSize = 0;
    //从第一个位置开始回溯
    backtrack(nums, numsSize, res, returnSize, returnColumnSizes, set, setSize, index);
    return res;
}
int main()
{
    int i, j, n;
    scanf("%d", &n);
    int *nums = (int *)malloc(sizeof(int) * n);
    int **res, *col, row;
    for (i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    res = subsets(nums, n, &row, &col);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col[i]; j++)
            printf("%d ", res[i][j]);
        printf("\n");
        free(res[i]);
    }
    free(res);
    free(nums);
    return 0;
}
