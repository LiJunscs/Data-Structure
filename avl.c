#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct TreeNode {
	struct TreeNode* parent;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
	int bf;//ƽ������
	int val;//�洢������
};
typedef struct TreeNode Tree;
void rotate_RR(Tree* root) {
	//���洫�����ĸ��ڵ��������
	Tree* rTree = root->rchild;
	//�޸�ƽ������
	root->bf = 0;
	rTree->bf = 0;
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
	lTree->bf = 0;
	root->bf = 0;
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
	else if (bf = 1) {
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
Tree* search_node(Tree* root, int val) {
	//���ݶ��������������ʣ��ȸ��ڵ������������Ҷ��ӣ��ȸ��ڵ�С��������ӣ����е�������
	Tree* cur = root;
	while (cur&&cur->val != val) {
		if (cur->val < val)
			cur = cur->rchild;
		else cur = cur->lchild;
	}
	return cur;
}
bool delete_node(Tree* root, int val) {
	Tree* cur = search_node(root, val);//���ҵ���Ҫɾ���Ľڵ�
	if (cur == NULL)//û�ҵ�ֱ�ӷ���false
		return false;
	if (cur->lchild == NULL && cur->rchild == NULL) {
		//����Ҫɾ������һ��Ҷ�ӽڵ㣬��ֱ��ɾ����Ȼ���Ե����ϵ���
		//�޸ı�ɾ���ڵ㸸�ڵ�����Ҷ���ָ���bfֵ
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
		free(cur);//�ͷ��ڴ�
		//�ӱ�ɾ���ڵ�ĸ��ڵ㿪ʼ�����ϵ���������
		while (pParent) {
			/*������ڵ��bfֵ�����1�� - 1��˵�����ڵ��ԭ�ȵ�bfֵΪ0��
			���ڸ��߲�εĸ��ڵ���˵����������ĸ߶�û�з����仯������Ҫ����*/
			if (pParent->bf == 1|| pParent->bf == -1)
				break;
			//�����ڵ�ĸ߶ȱ����0����˵���߲����ĳһ�����ĸ߶ȱ�ͣ���Ҫ���ϵ���
			else if (pParent->bf == 0) {
				if (pParent == pParent->parent->lchild)
					pParent->parent->bf++;
				else pParent->parent->bf--;
				pParent = pParent->parent;
			}
			else {//�����ڵ��bfֵ���2��-2����ֱ���ж����ͣ����е���
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
				break;//ͨ��ֻ�ƻ�һ��
			}//end if �ж��Ƿ���Ҫ����
		}//end while
		return true;
	}//end if �ж��Ƿ�ɾ��Ҷ�ڵ�
	else if (cur->lchild) {
		//�����ɾ���ڵ㲻��Ҷ�ڵ㣬����ȥѰ������������������ֵ�������ֵ������ɾ���Ľڵ㣬Ȼ��ɾ������Ľڵ㼴��
		Tree* dNode = cur->lchild;
		//Ѱ�������������ֵ
		while (dNode->rchild)
			dNode = dNode->rchild;
		//�޸ı�ɾ���ڵ�
		cur->val = dNode->val;
		//ɾ���������е���ͬ����
		return delete_node(cur->lchild, dNode->val);
	}
	else {
		//�����ɾ���ڵ㲻��Ҷ�ӽڵ㣬Ҳû������������Ѱ�������������е���Сֵ��Ȼ�����ֵ������ɾ���ڵ㣬ת��ɾ���ҵ��Ľڵ�
		Tree* dNode = cur->rchild;
		//Ѱ������������Сֵ
		while (dNode->lchild)
			dNode = dNode->lchild;
		//�޸ı�ɾ���ڵ�
		cur->val = dNode->val;
		//ɾ���������е���ͬ����
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