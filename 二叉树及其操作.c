#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
int Max(int a, int b) {
    return a >= b ? a : b;
}
//BFS构造二叉树
struct TreeNode* create_tree(int* nums, int n) {
    int front = 0, rear = 0, size = 0, i = 0, j = 0;
    struct TreeNode** queue = NULL, * tmp = NULL, * newNode = NULL;
    queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * n);
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = nums[j++];
    root->left = NULL;
    root->right = NULL;
    queue[rear++] = root;
    while (front != rear && j < n) {
        size = rear - front;
        for (i = 0; i < size; i++) {
            tmp = queue[front];
            if (j < n) {
                if (nums[j] == -1000) {
                    tmp->left = NULL;
                    j++;
                }
                else {
                    tmp->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                    tmp->left->val = nums[j++];
                    tmp->left->left = NULL;
                    tmp->left->right = NULL;
                    queue[rear++] = tmp->left;
                }
            }
            if (j < n) {
                if (nums[j] == -1000) {
                    tmp->right = NULL;
                    j++;
                }
                else {
                    tmp->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                    tmp->right->val = nums[j++];
                    tmp->right->left = NULL;
                    tmp->right->right = NULL;
                    queue[rear++] = tmp->right;
                }
            }
            front++;
        }
    }
    return root;
}
//求树高
int TreeHeight(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    else return 1 + Max(TreeHeight(root->left), TreeHeight(root->right));
}
//二叉树前序遍历_递归版
void pre_order_traversal(struct TreeNode* root, int* nums, int* n) {
    if (root) {
        nums[*n] = root->val;
        (*n)++;
        pre_order_traversal(root->left, nums, n);
        pre_order_traversal(root->right, nums, n);
    }
}
//根据前序遍历和中序遍历建立二叉树
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (inorderSize <= 0)
        return NULL;
    int i;
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = preorder[0];
    newNode->left = NULL;
    newNode->right = NULL;
    for (i = 0; i < inorderSize; i++)
        if (inorder[i] == newNode->val)
            break;
    if (i == inorderSize)
        return newNode;
    newNode->left = buildTree(&preorder[1], i, inorder, i);
    newNode->right = buildTree(&preorder[i + 1], preorderSize - i - 1, &inorder[i + 1], inorderSize - i - 1);
    return newNode;
}
//释放二叉树
void freeTree(struct TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

