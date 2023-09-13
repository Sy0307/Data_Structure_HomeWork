#include <bits/stdc++.h>

struct node
{
    int data;
    node *left, *right;
};
// Q1 时间复杂度 O(logn)
void delete_max_element(node *root)
{
    if (root == nullptr)
        return;
    if (root->right == nullptr)
    {
        auto tmp = root;
        root = root->left;
        delete tmp;
    }
    else
        delete_max_element(root->right);
}

// Q2 在二叉搜索树上插入一个元素
void insert(node *root, int x)
{
    if (root == nullptr)
    {
        root = new node;
        root->data = x;
        root->left = root->right = nullptr;
    }
    else if (x < root->data)
        insert(root->left, x);
    else
        insert(root->right, x);
}

class AVLTree
{
private:
    struct node
    {
        int data;
        int height;
        node *left, *right;
        node(int x) : data(x), height(0), left(nullptr), right(nullptr) {}
    };
    node *root;
    void insert(node *&root, int x)
    {
        if (root == nullptr)
        {
            root = new node(x);
            return;
        }
        if (x < root->data)
            insert(root->left, x);
        else
            insert(root->right, x);
        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        if (getHeight(root->left) - getHeight(root->right) == 2)
        {
            if (x < root->left->data)
                LL(root);
            else
                LR(root);
        }
        else if (getHeight(root->right) - getHeight(root->left) == 2)
        {
            if (x > root->right->data)
                RR(root);
            else
                RL(root);
        }
    }
    void LL(node *&root)
    {
        auto tmp = root->left;
        root->left = tmp->right;
        tmp->right = root;
        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        tmp->height = std::max(getHeight(tmp->left), root->height) + 1;
        root = tmp;
    }
    void RR(node *&root)
    {
        auto tmp = root->right;
        root->right = tmp->left;
        tmp->left = root;
        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        tmp->height = std::max(getHeight(tmp->right), root->height) + 1;
        root = tmp;
    }
    void LR(node *&root)
    {
        RR(root->left);
        LL(root);
    }
    void RL(node *&root)
    {
        LL(root->right);
        RR(root);
    }
    int getHeight(node *root)
    {
        if (root == nullptr)
            return -1;
        return root->height;
    }
    // Q3 输出所有节点的平衡因子
    void printBalanceFactor(node *root)
    {
        if (root == nullptr)
            return;
        std::cout << root->data << " " << getHeight(root->left) - getHeight(root->right) << std::endl;
        printBalanceFactor(root->left);
        printBalanceFactor(root->right);
    }
};

// Q4 如上
// Q5 实现一棵4阶B-树
class BTree
{
private:
    struct node
    {
        int data[3];
        node *child[4];
        int cnt;
        node(int x) : cnt(1)
        {
            data[0] = x;
            for (int i = 0; i < 4; i++)
                child[i] = nullptr;
        }
    };
    node *root;
    void insert(node *&root, int x)
    {
        if (root == nullptr)
        {
            root = new node(x);
            return;
        }
        if (root->cnt == 3)
        {
            auto tmp = new node(root->data[1]);
            tmp->child[0] = root;
            tmp->child[1] = new node(root->data[2]);
            tmp->child[1]->child[0] = root->child[2];
            tmp->child[1]->child[1] = root->child[3];
            root->cnt = 1;
            root->child[0] = tmp;
            root->child[1] = root->child[2] = root->child[3] = nullptr;
            insert(root, x);
        }
        else
        {
            if (x < root->data[0])
                insert(root->child[0], x);
            else if (x > root->data[root->cnt - 1])
                insert(root->child[root->cnt], x);
            else
                insert(root->child[1], x);
        }
    }
};