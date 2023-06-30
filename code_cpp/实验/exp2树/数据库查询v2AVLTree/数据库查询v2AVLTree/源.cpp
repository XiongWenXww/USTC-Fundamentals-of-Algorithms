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

#include<iomanip>
#include<iostream>
#include<string.h>
#define N 2000
using namespace std;

template<class T>
class AVLTreeNode
{
public:
    T key;    // �ؼ��֣���ֵ��
    int height;    // �߶�
    AVLTreeNode* left;    // ����
    AVLTreeNode* right;    // �Һ���
    AVLTreeNode* parent;

    AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r, AVLTreeNode* p) :
        key(value), left(l), right(r), parent(p) {}
};

template<class T>
class AVLTree
{
private:
    AVLTreeNode<T>* root;    // �����

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

    // LL�������Ӧ�����(����ת)
    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);
    // RR�����Ҷ�Ӧ�����(�ҵ���ת)
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);
    // LR�����Ҷ�Ӧ�����(��˫��ת)
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);
    // RL�������Ӧ�����(��˫��ת)
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
        // �½���� 
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
        // ���������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���
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
        // ���������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���
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

//�������������û��
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
//            while (true) {      // ��������ȵ����
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