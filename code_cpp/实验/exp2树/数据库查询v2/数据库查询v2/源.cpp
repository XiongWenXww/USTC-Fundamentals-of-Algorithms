//�ڷܵ�С��Ϊ��Ԥϰ��ѧ�ڵ����ݿ�γ̣���������ʵ��һ���򵥵����ݿ�ϵͳ�������ݿ�ϵͳ��Ҫ�����û���
//���ݿ����Ͳ�ѯ��䣬�������Ӧ�������������˵���û������빲�����������������Ͳ�ѯ��䡣����ÿ
//������������һ���Ǹ�������ʾ��Ҫ��������ݡ�ÿ����ѯ������һ��������ʾ����ѯ�ļ�ֵ�����ü�ֵ��
//����ֱ������ü�ֵ������������ݿ��бȸü�ֵС������ֵ��
//input:�����������в�����䣬ÿ�еĸ�ʽΪ���µ�һ�֣�
//        INSERT keykey
//        FIND keykey
//        ��󵥶���һ��EXIT��ʾ���������
//output: ��ÿ����ѯ������һ�У�ÿ�����1�����֣���ʾ��ѯ�Ľ����
//        �ü�ֵ������ֱ������ü�ֵ������������ݿ��бȸü�ֵС������ֵ��
//
//sample input: 
//INSERT 7
//INSERT 11
//INSERT 2
//FIND 2
//INSERT 5
//INSERT 3
//FIND 4
//FIND 7
//EXIT
//
//sample output:
//2
//3
//7
#include<iostream>
#include<stdio.h>
#include<string.h>

#define N 2000

using namespace std;

class BSTNode {
public:
	int key;
	BSTNode* lchild, * rchild, * parent;

	BSTNode(int value) :key(value) {
		lchild = NULL;
		rchild = NULL;
		parent = NULL;
	}

	BSTNode(int value, BSTNode* l, BSTNode* r, BSTNode* p) :key(value), lchild(l), rchild(r), parent(p) {}
};

class BSTree {
private:
	BSTNode* root;

public:
	
	BSTree() {
		root = NULL;
	}
	~BSTree();

	void insert(const int& value);
	//void InOrder();
	BSTNode* FindKey(const int& value);
	BSTNode* Predecessor(BSTNode* p);

private:
	void insert(BSTNode* p, BSTNode* node);
	//void InOrder(BSTNode* p);
	BSTNode* FindKey(BSTNode* p,const int& value);
};

void BSTree::insert(const int& value) {
	BSTNode* node = new BSTNode(value);
	node->key = value;
	node->lchild = node->rchild = node->parent = NULL;
	if (node == NULL) {
		printf("���ڴ���ã�\n");
	}

	if (root == NULL) {
		root = node;
	}
	else {
		insert(root, node);
	}
}

void BSTree::insert(BSTNode* p, BSTNode* node) {
	BSTNode* q = p;
	while (p != NULL) {
		q = p;	//��q����¼p��parent����Ȼ��ָ��parent��ָ�룬��ѭ��������Ϊ�ж�p�Ƿ�Ϊ�գ�
				//��ѭ������ʱpΪNULL����ʱ��ָ��parent��ָ��
		if (node->key < p->key) {
			p = p->lchild;
		}
		else {
			p = p->rchild;
		}
	}

	if (node->key < q->key) {
		q->lchild = node;
	}
	else {
		q->rchild = node;
	}
	node->parent = q;
}


//void BSTree::InOrder() {
//	if (root != NULL) {
//		//BSTNode* p = root;
//		InOrder(root);
//	}
//	
//}
//
//void BSTree::InOrder(BSTNode* p) {
//	if (p != NULL) {
//		InOrder(p->lchild);
//		printf("%d ", p->key);
//		InOrder(p->rchild);
//	}
//}

BSTNode* BSTree::FindKey(const int& value) {
	if (root != NULL) {
		return FindKey(root, value);
	}
	return NULL;
}

BSTNode* BSTree::FindKey(BSTNode* p, const int& value) {
	if (value == p->key) {
		return p;
	}
	BSTNode* q = p;
	while (p && value != p->key) {
		q = p;
		if (value < p->key) {
			p = p->lchild;
		}
		else {
			p = p->rchild;
		}
	}
	if (p != NULL) {	// �ҵ���
		return p;
	}
	else{	//û�ҵ������ر�valueС�������
		if (value > q->key) {
			return q;
		}
		else {
			return Predecessor(q);	// ����q��ǰ���ڵ�
		}
	}
}

BSTNode* BSTree::Predecessor(BSTNode* p) {
	if (root != NULL) {
		if (p->lchild != NULL) {
			p = p->lchild;
			while (p->rchild != NULL) {
				p = p->rchild;
			}
			return p;
		}
		else {
			BSTNode* q = p->parent;
			
			while (q != NULL && q->lchild == p) {
				p = q;
				q = p->parent;
			}
			return q;
		}
	}
	return NULL;
}

int main() {
	BSTree* BST = new BSTree();

	int result[N], n = 0;

	char c[7] = { 0 };
	char c1[7] = { 'I','N','S','E','R','T'};
	char c2[5] = { 'F','I','N','D' };
	char c3[5] = { 'E','X','I','T' };
	int num;
	scanf_s("%s", c, 7);
	while (true) {
		if (strcmp(c, c3) == 0) {
			break;
		}
		scanf_s("%d", &num);
		if (strcmp(c, c1) == 0) {
			BST->insert(num);
		}
		else {
			result[n] = BST->FindKey(num)->key;
			++n;
		}
		
		scanf_s("%s", c, 7);
	}

	for (int i = 0; i < n; ++i) {
		printf("%d\n", result[i]);
	}
}