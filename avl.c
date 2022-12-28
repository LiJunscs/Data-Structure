#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct TreeNode {
	struct TreeNode* parent;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
	int bf;//平衡因子
	int val;//存储的数据
};
typedef struct TreeNode Tree;
void rotate_RR(Tree* root) {
	//保存传进来的根节点的右子树
	Tree* rTree = root->rchild;
	//修改平衡因子
	root->bf = 0;
	rTree->bf = 0;
	//将右子树的的左子树给根节点，并修改其父节点
	root->rchild = rTree->lchild;
	if(rTree->lchild)
		rTree->lchild->parent = root;
	//判断根节点是其父节点的左右儿子，连接其右子树和父节点
	Tree* tmp = root->parent;
	if (tmp) {
		if (root == tmp->lchild)
			tmp->lchild = rTree;
		else tmp->rchild = rTree;
	}
	rTree->parent = tmp;
	//将根节点变成右子树的左子树，并修改其父节点
	rTree->lchild = root;
	root->parent = rTree;
}
void rotate_LL(Tree* root) {
	//保存传进来的根节点的左子树
	Tree* lTree = root->lchild;
	//修改平衡因子
	lTree->bf = 0;
	root->bf = 0;
	//将左子树的右子树给根节点，并修改其父节点
	root->lchild = lTree->rchild;
	if(lTree->rchild)
		lTree->rchild->parent = root;
	//判断根节点是其父节点左右儿子，连接其左子树其父节点
	Tree* tmp = root->parent;
	if (tmp) {
		if (root == tmp->lchild)
			tmp->lchild = lTree;
		else tmp->rchild = lTree;
	}
	lTree->parent = tmp;
	//将根节点变成左子树的左孩子，并修改其父节点
	lTree->rchild = root;
	root->parent = lTree;
}
void rotate_RL(Tree* root) {
	Tree* rc = root->rchild;
	int bf = rc->lchild->bf;
	//先进行右旋再进行左旋
	rotate_LL(root->rchild);
	rotate_RR(root);
	//根据不同情况，修改对应的bf值
	if (bf == -1) {
		root->bf = 0;
		rc->bf = 1;
	}
	else if (bf = 1) {
		root->bf = -1;
		rc->bf = 0;
	}

}
void rotate_LR(Tree* root) {
	Tree* lc = root->lchild;
	int  bf = lc->rchild->bf;
	//先进行右旋再进行左旋
	rotate_RR(root->lchild);
	rotate_LL(root);
	//根据情况修改对应的bf值
	if (bf == -1) {
		lc->bf = 0;
		root->bf = 1;
	}
	else if (bf == 1) {
		lc->bf = -1;
		root->bf = 0;
	}
}
Tree* create_node(int val) {
	Tree* node = (Tree*)malloc(sizeof(Tree));
	node->parent = NULL;
	node->lchild = NULL;
	node->rchild = NULL;
	node->val = val;
	node->bf = 0;
	return node;
}
Tree* insert_node(Tree* root, int val) {
	if (root == NULL) {
		root = create_node(val);
		return root;
	}
	Tree* cur = root;
	Tree* new_node = create_node(val);//创建一个新的节点待插入
	while (cur != NULL) {
		//根据二叉搜索树的性质往下搜寻直到找到一个空节点位置，放置新申请的节点
		//新申请节点父节点要跟随cur节点变化，保证其父节点随时可以找到
		if (val < cur->val) {
			new_node->parent = cur;
			cur = cur->lchild;
		}
		else if (val > cur->val) {
			new_node->parent = cur;
			cur = cur->rchild;
		}
		else {
			free(new_node);
			return root;
		}//如果遇见相同值的节点，则直接结束本次插入
	}//end while,此时找到了一个空节点位置，并且新节点的父节点已经找到
	//根据需要插入的值与父节点的值相比，判断新的节点在父节点的哪个位置，修改父节点的指针
	if (val < new_node->parent->val)
		new_node->parent->lchild = new_node;
	else new_node->parent->rchild = new_node;
	//从新申请的节点回溯，修改沿途节点bf值
	cur = new_node;
	while (cur->parent != NULL) {
		if (cur == cur->parent->lchild)//如果当前节点是父节点的左儿子，则父节点bf值-1
			cur->parent->bf--;
		else cur->parent->bf++;//如果当前节点是父节点右儿子，则父节点bf值+1
		//检查当前父节点修改后的bf值
		if (cur->parent->bf == 0)//如果修改后的父节点的bf值等于0，则树已经达到平衡
			break;
		else if (cur->parent->bf == 1 || cur->parent->bf == -1) //如果父节点的值是-1或1，则父节点仍然平衡，不需要旋转，继续向上寻找
			cur = cur->parent;
		else {//其余的情况，父节点已经不平衡，分情况进行旋转
			if (cur->parent->bf == 2) {
				//此时，右子树比左子树高，需要进行左旋，分左旋和右左旋两种情况
				/*两种情况的判定根据当前节点的bf值来算，若当前节点bf值为1，说明当前节点的右子树高与左子树,
				/*即在右子树的右子树上插入了新节点，为RR型旋转*/
				/*若当前节点的bf值为-1，说明当前节点的左子树较高，即在右子树的左子树上插入了新节点，需要RL型旋转*/
				if (cur->bf == 1) {
					rotate_RR(cur->parent);
					//若cur的父节点是根节点，RR旋转将cur变成根节点，其父节点变成cur的左儿子，故需要改变根节点的指针
					if (root->parent != NULL)
						root = root->parent;
				}
				else {
					rotate_RL(cur->parent);
					if (root->parent != NULL)
						root = root->parent;
				}
			}
			else {
				//此时，左子树比右子树高，需要进行右旋，分右旋和左右旋两种情况
				/*两种情况的判定根据当前节点的bf值来算，若当前节点bf值为-1，说明当前节点的左子树高于右子树，
				/*即在左子树的左子树上插入新阶段，为LL型旋转*/
				/*若当前节点的bf值为1，说明当前节点的右子树较高，即在左子树的右子树上插入了新节点，为LR型旋转*/
				if (cur->bf == -1) {
					rotate_LL(cur->parent);
					if (root->parent != NULL)
						root = root->parent;
				}
				else {
					rotate_LR(cur->parent);
					if (root->parent != NULL)
						root = root->parent;
				}
			}
			break;//旋转结束后，上层节点也一定会平衡，故直接退出
		}//end if
	}//end while
	return root;
}
Tree* search_node(Tree* root, int val) {
	//根据二叉搜索树的性质，比根节点的数大的数在右儿子，比根节点小的在左儿子，进行迭代即可
	Tree* cur = root;
	while (cur&&cur->val != val) {
		if (cur->val < val)
			cur = cur->rchild;
		else cur = cur->lchild;
	}
	return cur;
}
bool delete_node(Tree* root, int val) {
	Tree* cur = search_node(root, val);//先找到需要删除的节点
	if (cur == NULL)//没找到直接返回false
		return false;
	if (cur->lchild == NULL && cur->rchild == NULL) {
		//若需要删除的是一个叶子节点，则直接删除，然后自底向上调整
		//修改被删除节点父节点的左右儿子指针和bf值
		Tree* pParent = cur->parent;
		if (pParent == NULL) {
			free(cur);
			return true;
		}
		if (cur == pParent->lchild) {
			pParent->lchild = NULL;
			pParent->bf++;
		}
		else {
			pParent->rchild = NULL;
			pParent->bf--;
		}
		free(cur);//释放内存
		//从被删除节点的父节点开始，向上调整整棵树
		while (pParent) {
			/*如果父节点的bf值变成了1或 - 1，说明父节点的原先的bf值为0，
			对于更高层次的根节点来说，这棵子树的高度没有发生变化，不需要调整*/
			if (pParent->bf == 1|| pParent->bf == -1)
				break;
			//若父节点的高度变成了0，则说明高层的树某一子树的高度变低，需要向上调整
			else if (pParent->bf == 0) {
				if (pParent == pParent->parent->lchild)
					pParent->parent->bf++;
				else pParent->parent->bf--;
				pParent = pParent->parent;
			}
			else {//若父节点的bf值变成2或-2，则直接判断类型，进行调整
				if (pParent->bf == 2) {
					if (pParent->rchild->bf == 1)
						rotate_RR(pParent);
					else rotate_RL(pParent);
				}
				else {
					if (pParent->lchild->bf == -1)
						rotate_LL(pParent);
					else rotate_LR(pParent);
				}//end if
				break;//通常只破坏一处
			}//end if 判断是否需要调整
		}//end while
		return true;
	}//end if 判断是否删除叶节点
	else if (cur->lchild) {
		//如果被删除节点不是叶节点，则先去寻找它的左子树中最大的值，将这个值赋给被删除的节点，然后删除下面的节点即可
		Tree* dNode = cur->lchild;
		//寻找左子树的最大值
		while (dNode->rchild)
			dNode = dNode->rchild;
		//修改被删除节点
		cur->val = dNode->val;
		//删除左子树中的相同顶点
		return delete_node(cur->lchild, dNode->val);
	}
	else {
		//如果被删除节点不是叶子节点，也没有左子树，则寻找它的右子树中的最小值，然后将这个值赋给被删除节点，转而删除找到的节点
		Tree* dNode = cur->rchild;
		//寻找右子树的最小值
		while (dNode->lchild)
			dNode = dNode->lchild;
		//修改被删除节点
		cur->val = dNode->val;
		//删除右子树中的相同顶点
		return delete_node(cur->rchild, dNode->val);
	}
	return true;
}
int main() {
	int val = 0;
	Tree* root = NULL;
	while (val != -1) {
		scanf("%d", &val);
		root = insert_node(root, val);
	}
	while (val != 0) {
		bool state = delete_node(root, val);
		printf("%d\n", state);
		scanf("%d", &val);
	}
	return 0;
}