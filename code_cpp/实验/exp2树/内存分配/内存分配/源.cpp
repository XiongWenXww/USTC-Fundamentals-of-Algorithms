//input:
//输入数据共n + 1行。第一行一个整数n表示共需要处理n次内存分配。
//然后是n行数据，每行的格式为:a b,表示申请区间为[a, b]
//数据规模：
//n≤1,000,000
//0≤a≤b≤2^30
//output:
//输出共nn行。
//对于每行内存分配的申请，若申请成功则输出一行0，若申请失败则输出一行-1。
//sample input:
//5
//0 1
//8 9
//5 7
//1 2
//2 4
//sample output:
//0
//0
//0
//- 1
//0
#include<iostream>
#include<stdio.h>
#define N 11000
#define M 1000

using namespace std;

//基于key的AVL树（比较key的大小进行相关操作而非rkey）
template<class T>
class AVLTreeNode {
public:
    T key, rkey;    //表示区间[key,rkey]     
    int height;
    AVLTreeNode* left;
    AVLTreeNode* right;
    AVLTreeNode* parent;

    AVLTreeNode(T a, T b, AVLTreeNode* l, AVLTreeNode* r, AVLTreeNode* p) :
        key(a), rkey(b), left(l), right(r), parent(p) {}
};

template<class T>
class AVLTree {
private:
    AVLTreeNode<T>* root;    // 根结点

public:
    AVLTree();
    ~AVLTree();

    int height();
    T minimum();
    T maximum();
    void insert(T a, T b);
    bool isOverlap(T a, T b);

private:
    int height(AVLTreeNode<T>* tree);

    AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T a, T b);
    bool isOverlap(AVLTreeNode<T>* tree, T a, T b);   // 看区间[a,b]是否与树中的区间重叠

    // LL：左左对应的情况(左单旋转)
    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);
    // RR：右右对应的情况(右单旋转)
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);
    // LR：左右对应的情况(左双旋转)
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);
    // RL：右左对应的情况(右双旋转)
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);
};

template<class T>
AVLTree<T>::AVLTree() : root(NULL) {
}

template<class T>
AVLTree<T>::~AVLTree() {
    destroy(root);
}

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree) {
    if (tree != NULL)
        return tree->height;
    return 0;
}

template<class T>
int AVLTree<T>::height() {
    return height(root);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2) {
    AVLTreeNode<T>* k1;

    k1 = k2->left;  k1->parent = k2->parent;
    k2->left = k1->right;
    if (k2->left) {
        k2->left->parent = k2;
    }
    k1->right = k2;     k2->parent = k1;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;

    return k1;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1) {
    AVLTreeNode<T>* k2;

    k2 = k1->right;     k2->parent = k1->parent;
    k1->right = k2->left;
    if (k1->right) {
        k1->right->parent = k1;
    }
    k2->left = k1;  k1->parent = k2;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(k1->height, height(k2->right)) + 1;

    return k2;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3) {
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1) {
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& tree, T a, T b) {
    if (tree == NULL)
    {
        // 新建结点 
        tree = new AVLTreeNode<T>(a, b, NULL, NULL, NULL);
        if (tree == NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (a < tree->key) {
        AVLTreeNode<T>* p = insert(tree->left, a, b);
        tree->left = p;
        p->parent = tree;
        // 插入结点后，若AVL树失去平衡，则进行相应的调节
        if (height(tree->left) - height(tree->right) == 2) {
            if (a < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else {
        AVLTreeNode<T>* p = insert(tree->right, a, b);
        tree->right = p;
        p->parent = tree;
        // 插入结点后，若AVL树失去平衡，则进行相应的调节
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (a > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;

    return tree;
}

template<class T>
void AVLTree<T>::insert(T a, T b) {
    insert(root, a, b);
}

template<class T>
bool AVLTree<T>::isOverlap(AVLTreeNode<T>* p, T a, T b) {
    while (p != NULL) {
        if (a <= p->rkey && b >= p->key) {      // 区间重叠
            return true;
        }
        if (b < p->key) {
            p = p->left;
        }
        else {
            p = p->right;
        }
    }
    return false;   // 未找到重叠的区间
}

template<class T>
bool AVLTree<T>::isOverlap(T a, T b) {
    if (root == NULL) {
        return false;
    }
    return isOverlap(root, a, b);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree) {
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

template<class T>
T AVLTree<T>::minimum() {
    AVLTreeNode<T>* p = minimum(root);
    if (p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree) {
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

template<class T>
T AVLTree<T>::maximum() {
    AVLTreeNode<T>* p = maximum(root);
    if (p != NULL)
        return p->key;
    return (T)NULL;
}

int main() {
    AVLTree<int>* AVL = new AVLTree<int>();
    int result[M];
    int n, a, b;

    scanf_s("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf_s("%d %d", &a, &b);
        if (AVL->isOverlap(a, b) == false) {    // 没有区间重叠
            AVL->insert(a, b);
            result[i] = 0;
        }
        else {
            result[i] = -1;
        }

    }


    for (int i = 0; i < n; ++i) {
        printf("%d\n", result[i]);
    }
}