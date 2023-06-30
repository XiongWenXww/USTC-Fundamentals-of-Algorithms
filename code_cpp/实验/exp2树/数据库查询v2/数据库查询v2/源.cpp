//勤奋的小明为了预习下学期的数据库课程，决定亲自实现一个简单的数据库系统。该数据库系统需要处理用户的
//数据库插入和查询语句，并输出相应的输出。具体来说，用户的输入共包含若干条插入语句和查询语句。其中每
//条插入语句包含一个非负整数表示需要插入的数据。每条查询语句包含一个整数表示待查询的键值，若该键值存
//在则直接输出该键值，否则输出数据库中比该键值小的最大键值。
//input:首先是若干行插入语句，每行的格式为如下的一种：
//        INSERT keykey
//        FIND keykey
//        最后单独的一行EXIT表示输入结束。
//output: 对每条查询语句输出一行，每行输出1个数字，表示查询的结果。
//        该键值存在则直接输出该键值，否则输出数据库中比该键值小的最大键值。
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
		printf("无内存可用！\n");
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
		q = p;	//用q来记录p的parent，虽然有指向parent的指针，但循环的条件为判断p是否为空，
				//当循环结束时p为NULL，此时无指向parent的指针
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
	if (p != NULL) {	// 找到了
		return p;
	}
	else{	//没找到，返回比value小的最大结点
		if (value > q->key) {
			return q;
		}
		else {
			return Predecessor(q);	// 返回q的前驱节点
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