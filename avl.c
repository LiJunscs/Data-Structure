#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
struct TreeNode {
	struct TreeNode* parent;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
	int bf;//平衡因子
	int val;//存储的数据
};
typedef struct TreeNode Tree;
void rotate_RR(Tree*);
void rotate_RL(Tree*);
void rotate_LL(Tree*);
void rotate_LR(Tree*);
Tree* create_node(int);
Tree* insert_node(Tree*, int);
Tree* search_node(Tree*, int, int*);
bool delete_node(Tree**, int);
void free_tree(Tree*);
void print_tree(Tree*, int);
int main() {
	int val = 0, flag = 1;
	Tree* root = NULL;
	char filename[50] = "\0";
	FILE* fin;
	char fflag = 'n';
	printf("是否以文件数据建立查找树?(y/n) ");
	scanf("%c", &fflag);
	if (fflag == 'y') {
		printf("请输入文件名: ");
		getchar();
		scanf("%s", filename);
		fin = fopen(filename, "r");
		while (fscanf(fin, "%d", &val) != -1) {
			root = insert_node(root, val);
			//print_tree(root, 1);
		}
		fclose(fin);
	}
	while (flag) {
		printf("操作菜单：1:insert\t2:delete\t3:find\n\t  4:查看二叉树\t5:清屏\t\t6:quit\n");
		int order = 4, val = 0;
		printf("请选择操作: ");
		scanf("%d", &order);
		switch (order) {
		case 1:printf("请输入需要插入的关键字: ");
			scanf("%d", &val); 
			root = insert_node(root, val); 
			break;
		case 2:
			if (root == NULL) {
				printf("当前树为空，请重新选择\n");
				break;
			}
			printf("请输入需要删除的关键字: ");
			scanf("%d", &val);
			bool res = delete_node(&root, val);
			if (res) printf("删除成功\n");
			else printf("需要删除的关键字不存在\n");
			break;
		case 3:
			if (root == NULL) {
				printf("当前树为空，请重新选择\n");
				break;
			}
			printf("请输入需要查找的关键字: ");
			scanf("%d", &val);
			int cnt = 0;
			double duration = 0.0;
			Tree* tmp = NULL;
			clock_t start = clock();
			for(int i=1;i<=100000;i++)
				tmp = search_node(root, val, &cnt);
			clock_t end = clock();
			duration = ((double)end - start) / 100000 / CLK_TCK;
			if (tmp) {
				printf("关键字为%d, 查找的比较次数为%d, 花费时间%.9lf\n", val, cnt / 100000 + 1, duration);
			}
			else printf("需要查找的关键字不存在, 查找比较次数为%d, 花费时间%.9lf\n", cnt / 100000 + 1, duration);
			break;
		case 4:
			if (root == NULL) {
				printf("当前树为空，请重新选择\n");
				break;
			}
			print_tree(root, 1); break;
		case 5:system("cls"); break;
		case 6:printf("欢迎再次使用A_A\n");
			flag = 0;
			free_tree(root);
			break;
		}
	}
	return 0;
}
void rotate_RR(Tree* root) {
	//保存传进来的根节点的右子树
	Tree* rTree = root->rchild;
	//修改平衡因子
	if (!root->lchild  && rTree->lchild && rTree->rchild) {//删除操作导致的特殊情况，左子树为空，右子树高度为2
		rTree->bf = -1;
		root->bf = 1;
	}
	else {//正常插入的情况
		root->bf = 0;
		rTree->bf = 0;
	}
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
	if (!root->rchild && lTree->lchild && lTree->rchild) {//删除操作导致的特殊情况，右子树为空，左子树高度为2
		lTree->bf = 1;
		root->bf = -1;
	}
	else {//正常插入的情况
		lTree->bf = 0;
		root->bf = 0;
	}
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
	else if (bf == 1) {
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
Tree* search_node(Tree* root, int val, int* cnt) {
	//根据二叉搜索树的性质，比根节点的数大的数在右儿子，比根节点小的在左儿子，进行迭代即可
	Tree* cur = root;
	while (cur&&cur->val != val) {
		(*cnt)++;
		if (cur->val < val)
			cur = cur->rchild;
		else cur = cur->lchild;
	}
	return cur;
}
bool delete_node(Tree** root, int val) {
	Tree* real = NULL,* pParent = NULL, * cur = *root;
	Tree* stack[20] = { NULL };//用一个栈保存删除过程中经过的顶点，便于后续调整
	int top = 0;
	//根据二叉搜索树的性质寻找需要被删除的节点,并将经过的路径保存到栈中
	while (cur && cur->val != val) {
		stack[top++] = cur;
		if (cur->val < val)
			cur = cur->rchild;
		else cur = cur->lchild;
	}
	if (cur == NULL)//如果需要删除的值不存在
		return false;
	if (cur->lchild && cur->rchild) {//需要删除的节点左右儿子都在，转化为删除前驱
		real = cur->lchild;
		stack[top++] = cur;
		while (real->rchild) {
			stack[top++] = real;
			real = real->rchild;
		}
		cur->val = real->val;
		cur = real;
	}
	//以cur作为实际要删除的节点，real作为实际保留的节点
	if (cur->lchild) //如果只有左儿子，则只需要将左儿子变成现任父亲的左儿子即可
		real = cur->lchild;
	else real = cur->rchild;//如果只有右儿子，则只需要将右儿子变成现任父亲的右儿子即可
	if (cur->parent == NULL)//如果删除目标是整个AVL树的根节点
		*root = real;
	else {//根据被删除节点是其父节点的左右儿子来改变其现任左右儿子和bf值
		pParent = stack[top - 1];//从栈中查看第一个父节点
		if (cur == pParent->lchild) {
			pParent->lchild = real;
			if(real)
				real->parent = pParent;
		}
		else {
			pParent->rchild = real;
			if (real)
				real->parent = pParent;
		}
	}
	free(cur);//释放真正被删除节点的内存
	cur = real;//从新的儿子节点开始，向上调整
	while (top > 0) {
		pParent = stack[--top];//从栈中取出当前节点的父节点
		if (pParent->lchild == NULL && pParent->rchild == NULL)
			pParent->bf = 0;
		else {
			if (cur == pParent->lchild)
				pParent->bf++;
			else pParent->bf--;
		}
		/*如果父节点的bf值变成了1或 - 1，说明父节点的原先的bf值为0，
		对于更高层次的根节点来说，这棵子树的高度没有发生变化，不需要调整*/
		if (pParent->bf == 1 || pParent->bf == -1)
			break;
		//若父节点的bf值变成了0，则说明高层的树某一子树的高度变低，需要向上调整
		else if (pParent->bf == 0) 
			cur = pParent;
		else {//若父节点的bf值变成2或-2，则直接判断类型，进行调整
			if (pParent->bf == 2) {
				if (pParent->rchild->bf == 1 || pParent->rchild->bf == 0)//在删除一个节点导致某一棵子树为空时，可能出现另一半子树的bf值为0的情况
					rotate_RR(pParent);
				else rotate_RL(pParent);
				if ((* root)->parent)//若根节点被改变，则新的根节点为原根节点的父节点
					*root = (*root)->parent;
			}
			else {
				if (pParent->lchild->bf == -1 || pParent->lchild->bf == 0)
					rotate_LL(pParent);
				else rotate_LR(pParent);
				if ((*root)->parent)
					*root = (*root)->parent;
			}
			cur = pParent->parent;//由于旋转，下一轮调整的儿子节点变成现在的父节点的父节点
		}
	}
	return true;
}
void free_tree(Tree* root) {
	if (root) {
		free_tree(root->lchild);
		free_tree(root->rchild);
		free(root);
	}
}
void print_tree(Tree* root, int depth) {
	if (root) {
		for (int i = 1; i <= depth; i++)
			printf("*");
		printf("%d\n", root->val);
		print_tree(root->lchild, depth+1);
		print_tree(root->rchild, depth+1);
	}
}