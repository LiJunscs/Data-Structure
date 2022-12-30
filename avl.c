#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
struct TreeNode {
	struct TreeNode* parent;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
	int bf;//ƽ������
	int val;//�洢������
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
	printf("�Ƿ����ļ����ݽ���������?(y/n) ");
	scanf("%c", &fflag);
	if (fflag == 'y') {
		printf("�������ļ���: ");
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
		printf("�����˵���1:insert\t2:delete\t3:find\n\t  4:�鿴������\t5:����\t\t6:quit\n");
		int order = 4, val = 0;
		printf("��ѡ�����: ");
		scanf("%d", &order);
		switch (order) {
		case 1:printf("��������Ҫ����Ĺؼ���: ");
			scanf("%d", &val); 
			root = insert_node(root, val); 
			break;
		case 2:
			if (root == NULL) {
				printf("��ǰ��Ϊ�գ�������ѡ��\n");
				break;
			}
			printf("��������Ҫɾ���Ĺؼ���: ");
			scanf("%d", &val);
			bool res = delete_node(&root, val);
			if (res) printf("ɾ���ɹ�\n");
			else printf("��Ҫɾ���Ĺؼ��ֲ�����\n");
			break;
		case 3:
			if (root == NULL) {
				printf("��ǰ��Ϊ�գ�������ѡ��\n");
				break;
			}
			printf("��������Ҫ���ҵĹؼ���: ");
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
				printf("�ؼ���Ϊ%d, ���ҵıȽϴ���Ϊ%d, ����ʱ��%.9lf\n", val, cnt / 100000 + 1, duration);
			}
			else printf("��Ҫ���ҵĹؼ��ֲ�����, ���ұȽϴ���Ϊ%d, ����ʱ��%.9lf\n", cnt / 100000 + 1, duration);
			break;
		case 4:
			if (root == NULL) {
				printf("��ǰ��Ϊ�գ�������ѡ��\n");
				break;
			}
			print_tree(root, 1); break;
		case 5:system("cls"); break;
		case 6:printf("��ӭ�ٴ�ʹ��A_A\n");
			flag = 0;
			free_tree(root);
			break;
		}
	}
	return 0;
}
void rotate_RR(Tree* root) {
	//���洫�����ĸ��ڵ��������
	Tree* rTree = root->rchild;
	//�޸�ƽ������
	if (!root->lchild  && rTree->lchild && rTree->rchild) {//ɾ���������µ����������������Ϊ�գ��������߶�Ϊ2
		rTree->bf = -1;
		root->bf = 1;
	}
	else {//������������
		root->bf = 0;
		rTree->bf = 0;
	}
	//���������ĵ������������ڵ㣬���޸��丸�ڵ�
	root->rchild = rTree->lchild;
	if(rTree->lchild)
		rTree->lchild->parent = root;
	//�жϸ��ڵ����丸�ڵ�����Ҷ��ӣ��������������͸��ڵ�
	Tree* tmp = root->parent;
	if (tmp) {
		if (root == tmp->lchild)
			tmp->lchild = rTree;
		else tmp->rchild = rTree;
	}
	rTree->parent = tmp;
	//�����ڵ����������������������޸��丸�ڵ�
	rTree->lchild = root;
	root->parent = rTree;
}
void rotate_LL(Tree* root) {
	//���洫�����ĸ��ڵ��������
	Tree* lTree = root->lchild;
	//�޸�ƽ������
	if (!root->rchild && lTree->lchild && lTree->rchild) {//ɾ���������µ����������������Ϊ�գ��������߶�Ϊ2
		lTree->bf = 1;
		root->bf = -1;
	}
	else {//������������
		lTree->bf = 0;
		root->bf = 0;
	}
	//���������������������ڵ㣬���޸��丸�ڵ�
	root->lchild = lTree->rchild;
	if(lTree->rchild)
		lTree->rchild->parent = root;
	//�жϸ��ڵ����丸�ڵ����Ҷ��ӣ��������������丸�ڵ�
	Tree* tmp = root->parent;
	if (tmp) {
		if (root == tmp->lchild)
			tmp->lchild = lTree;
		else tmp->rchild = lTree;
	}
	lTree->parent = tmp;
	//�����ڵ��������������ӣ����޸��丸�ڵ�
	lTree->rchild = root;
	root->parent = lTree;
}
void rotate_RL(Tree* root) {
	Tree* rc = root->rchild;
	int bf = rc->lchild->bf;
	//�Ƚ��������ٽ�������
	rotate_LL(root->rchild);
	rotate_RR(root);
	//���ݲ�ͬ������޸Ķ�Ӧ��bfֵ
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
	//�Ƚ��������ٽ�������
	rotate_RR(root->lchild);
	rotate_LL(root);
	//��������޸Ķ�Ӧ��bfֵ
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
	Tree* new_node = create_node(val);//����һ���µĽڵ������
	while (cur != NULL) {
		//���ݶ���������������������Ѱֱ���ҵ�һ���սڵ�λ�ã�����������Ľڵ�
		//������ڵ㸸�ڵ�Ҫ����cur�ڵ�仯����֤�丸�ڵ���ʱ�����ҵ�
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
		}//���������ֵͬ�Ľڵ㣬��ֱ�ӽ������β���
	}//end while,��ʱ�ҵ���һ���սڵ�λ�ã������½ڵ�ĸ��ڵ��Ѿ��ҵ�
	//������Ҫ�����ֵ�븸�ڵ��ֵ��ȣ��ж��µĽڵ��ڸ��ڵ���ĸ�λ�ã��޸ĸ��ڵ��ָ��
	if (val < new_node->parent->val)
		new_node->parent->lchild = new_node;
	else new_node->parent->rchild = new_node;
	//��������Ľڵ���ݣ��޸���;�ڵ�bfֵ
	cur = new_node;
	while (cur->parent != NULL) {
		if (cur == cur->parent->lchild)//�����ǰ�ڵ��Ǹ��ڵ������ӣ��򸸽ڵ�bfֵ-1
			cur->parent->bf--;
		else cur->parent->bf++;//�����ǰ�ڵ��Ǹ��ڵ��Ҷ��ӣ��򸸽ڵ�bfֵ+1
		//��鵱ǰ���ڵ��޸ĺ��bfֵ
		if (cur->parent->bf == 0)//����޸ĺ�ĸ��ڵ��bfֵ����0�������Ѿ��ﵽƽ��
			break;
		else if (cur->parent->bf == 1 || cur->parent->bf == -1) //������ڵ��ֵ��-1��1���򸸽ڵ���Ȼƽ�⣬����Ҫ��ת����������Ѱ��
			cur = cur->parent;
		else {//�������������ڵ��Ѿ���ƽ�⣬�����������ת
			if (cur->parent->bf == 2) {
				//��ʱ�����������������ߣ���Ҫ�������������������������������
				/*����������ж����ݵ�ǰ�ڵ��bfֵ���㣬����ǰ�ڵ�bfֵΪ1��˵����ǰ�ڵ������������������,
				/*�������������������ϲ������½ڵ㣬ΪRR����ת*/
				/*����ǰ�ڵ��bfֵΪ-1��˵����ǰ�ڵ���������ϸߣ��������������������ϲ������½ڵ㣬��ҪRL����ת*/
				if (cur->bf == 1) {
					rotate_RR(cur->parent);
					//��cur�ĸ��ڵ��Ǹ��ڵ㣬RR��ת��cur��ɸ��ڵ㣬�丸�ڵ���cur������ӣ�����Ҫ�ı���ڵ��ָ��
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
				//��ʱ�����������������ߣ���Ҫ�������������������������������
				/*����������ж����ݵ�ǰ�ڵ��bfֵ���㣬����ǰ�ڵ�bfֵΪ-1��˵����ǰ�ڵ��������������������
				/*�������������������ϲ����½׶Σ�ΪLL����ת*/
				/*����ǰ�ڵ��bfֵΪ1��˵����ǰ�ڵ���������ϸߣ��������������������ϲ������½ڵ㣬ΪLR����ת*/
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
			break;//��ת�������ϲ�ڵ�Ҳһ����ƽ�⣬��ֱ���˳�
		}//end if
	}//end while
	return root;
}
Tree* search_node(Tree* root, int val, int* cnt) {
	//���ݶ��������������ʣ��ȸ��ڵ������������Ҷ��ӣ��ȸ��ڵ�С��������ӣ����е�������
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
	Tree* stack[20] = { NULL };//��һ��ջ����ɾ�������о����Ķ��㣬���ں�������
	int top = 0;
	//���ݶ���������������Ѱ����Ҫ��ɾ���Ľڵ�,����������·�����浽ջ��
	while (cur && cur->val != val) {
		stack[top++] = cur;
		if (cur->val < val)
			cur = cur->rchild;
		else cur = cur->lchild;
	}
	if (cur == NULL)//�����Ҫɾ����ֵ������
		return false;
	if (cur->lchild && cur->rchild) {//��Ҫɾ���Ľڵ����Ҷ��Ӷ��ڣ�ת��Ϊɾ��ǰ��
		real = cur->lchild;
		stack[top++] = cur;
		while (real->rchild) {
			stack[top++] = real;
			real = real->rchild;
		}
		cur->val = real->val;
		cur = real;
	}
	//��cur��Ϊʵ��Ҫɾ���Ľڵ㣬real��Ϊʵ�ʱ����Ľڵ�
	if (cur->lchild) //���ֻ������ӣ���ֻ��Ҫ������ӱ�����θ��׵�����Ӽ���
		real = cur->lchild;
	else real = cur->rchild;//���ֻ���Ҷ��ӣ���ֻ��Ҫ���Ҷ��ӱ�����θ��׵��Ҷ��Ӽ���
	if (cur->parent == NULL)//���ɾ��Ŀ��������AVL���ĸ��ڵ�
		*root = real;
	else {//���ݱ�ɾ���ڵ����丸�ڵ�����Ҷ������ı����������Ҷ��Ӻ�bfֵ
		pParent = stack[top - 1];//��ջ�в鿴��һ�����ڵ�
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
	free(cur);//�ͷ�������ɾ���ڵ���ڴ�
	cur = real;//���µĶ��ӽڵ㿪ʼ�����ϵ���
	while (top > 0) {
		pParent = stack[--top];//��ջ��ȡ����ǰ�ڵ�ĸ��ڵ�
		if (pParent->lchild == NULL && pParent->rchild == NULL)
			pParent->bf = 0;
		else {
			if (cur == pParent->lchild)
				pParent->bf++;
			else pParent->bf--;
		}
		/*������ڵ��bfֵ�����1�� - 1��˵�����ڵ��ԭ�ȵ�bfֵΪ0��
		���ڸ��߲�εĸ��ڵ���˵����������ĸ߶�û�з����仯������Ҫ����*/
		if (pParent->bf == 1 || pParent->bf == -1)
			break;
		//�����ڵ��bfֵ�����0����˵���߲����ĳһ�����ĸ߶ȱ�ͣ���Ҫ���ϵ���
		else if (pParent->bf == 0) 
			cur = pParent;
		else {//�����ڵ��bfֵ���2��-2����ֱ���ж����ͣ����е���
			if (pParent->bf == 2) {
				if (pParent->rchild->bf == 1 || pParent->rchild->bf == 0)//��ɾ��һ���ڵ㵼��ĳһ������Ϊ��ʱ�����ܳ�����һ��������bfֵΪ0�����
					rotate_RR(pParent);
				else rotate_RL(pParent);
				if ((* root)->parent)//�����ڵ㱻�ı䣬���µĸ��ڵ�Ϊԭ���ڵ�ĸ��ڵ�
					*root = (*root)->parent;
			}
			else {
				if (pParent->lchild->bf == -1 || pParent->lchild->bf == 0)
					rotate_LL(pParent);
				else rotate_LR(pParent);
				if ((*root)->parent)
					*root = (*root)->parent;
			}
			cur = pParent->parent;//������ת����һ�ֵ����Ķ��ӽڵ������ڵĸ��ڵ�ĸ��ڵ�
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