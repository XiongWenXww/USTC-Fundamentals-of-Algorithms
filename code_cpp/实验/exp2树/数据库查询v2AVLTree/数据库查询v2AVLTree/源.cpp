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

#include<iomanip>
#include<iostream>
#include<string.h>
#define N 2000
using namespace std;

template<class T>
class AVLTreeNode
{
public:
    T key;    // 关键字（键值）
    int height;    // 高度
    AVLTreeNode* left;    // 左孩子
    AVLTreeNode* right;    // 右孩子
    AVLTreeNode* parent;

    AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r, AVLTreeNode* p) :
        key(value), left(l), right(r), parent(p) {}
};

template<class T>
class AVLTree
{
private:
    AVLTreeNode<T>* root;    // 根结点

public:
    AVLTree();
    ~AVLTree();

    int height();
    AVLTreeNode<T>* iterativeSearch(T key);
    AVLTreeNode<T>* predecessor(AVLTreeNode<T>* x) const;
    T minimum();
    T maximum();
    void insert(T key);

private:
    int height(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

    AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T key);

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
AVLTree<T>::AVLTree() : root(NULL)
{
}

template<class T>
AVLTree<T>::~AVLTree()
{
    destroy(root);
}

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
    if (tree != NULL)
        return tree->height;
    return 0;
}

template<class T>
int AVLTree<T>::height()
{
    return height(root);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
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
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
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
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& tree, T key)
{
    if (tree == NULL)
    {
        // 新建结点 
        tree = new AVLTreeNode<T>(key, NULL, NULL, NULL);
        if (tree == NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key)
    {
        AVLTreeNode<T>* p = insert(tree->left, key);
        tree->left = p;
        p->parent = tree;
        // 插入结点后，若AVL树失去平衡，则进行相应的调节
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else
    {
        AVLTreeNode<T>* p = insert(tree->right, key);
        tree->right = p;
        p->parent = tree;
        // 插入结点后，若AVL树失去平衡，则进行相应的调节
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;

    return tree;
}

template<class T>
void AVLTree<T>::insert(T key)
{
    insert(root, key);
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
{
    AVLTreeNode<T>* p = x;
    while (x != NULL && x->key != key)
    {
        p = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    if (x != NULL)
    {
        return x;
    }
    else
    {
        if (key > p->key)
            return p;
        else
            return predecessor(p);
    }
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(root, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::predecessor(AVLTreeNode<T>* p) const
{
    if (root != NULL)
    {
        if (p->left != NULL)
        {
            p = p->left;
            while (p->right != NULL)
            {
                p = p->right;
            }
            return p;
        }
        else
        {
            AVLTreeNode<T>* q = p->parent;

            while (q != NULL && q->left == p) {
                p = q;
                q = p->parent;
            }
            return q;
        }
    }
    return NULL;
}

//用以下这个函数没过
//template<class T>
//AVLTreeNode<T>* AVLTree<T>::predecessor(AVLTreeNode<T>* p) const{
//    if (root != NULL){
//        if (p->left != NULL){
//            p = p->left;
//            while (p->right != NULL){
//                p = p->right;
//            }
//            return p;
//        }
//        else{
//            T key = p->key;
//            AVLTreeNode<T>* q = root;
//
//            while (true) {      // 不存在相等的情况
//                if (key < q->key){
//                    q = q->left;
//                }
//                else{
//                    if (q->right && q->right->key >= key){
//                        break;
//                    }
//                    q = q->right;
//                }
//            }
//            return q;
//        }
//    }
//    return NULL;
//}


template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

template<class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T>* p = minimum(root);
    if (p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

template<class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T>* p = maximum(root);
    if (p != NULL)
        return p->key;
    return (T)NULL;
}

int main() {
    AVLTree<int>* AVL = new AVLTree<int>();
    int result[N], n = 0;

    char c[7] = { 0 };
    char c1[7] = { 'I','N','S','E','R','T' };
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
            AVL->insert(num);
        }
        else {
            result[n] = AVL->iterativeSearch(num)->key;
            ++n;
        }

        scanf_s("%s", c, 7);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\n", result[i]);
    }
}