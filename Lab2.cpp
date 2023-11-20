/*
    实验二
    二叉树的基本操作及哈夫曼树编码/译码系统的实现
*/

#include <bits/stdc++.h>
using namespace std;

#define ElementType char
class btnode
{
    ElementType element;
    btnode *left, *right;
    //
public:
    btnode *PreCreatBt(btnode *t)
    {
        char c;
        cin >> c;
        if (c == '#')
        {
            t = nullptr;
        }
        else
        {
            t = new btnode;
            t->element = c;
            t->left = PreCreatBt(t->left);
            t->right = PreCreatBt(t->right);
        }
    }
    void PreOrderTransverse(btnode *t)
    {
        if (t == nullptr)
            return;

        cout << t->element;
        PreOrderTransverse(t->left);
        PreOrderTransverse(t->right);
    }
    void InOrderTransverse(btnode *t)
    {
        if (t == nullptr)
            return;

        InOrderTransverse(t->left);
        cout << t->element;
        InOrderTransverse(t->right);
    }
    void PostOrderTransverse(btnode *t)
    {
        if (t == nullptr)
            return;

        PostOrderTransverse(t->left);
        PostOrderTransverse(t->right);
        cout << t->element;
    }
    /*
    二叉树的基本操作
    1.求二叉树结点个数
    2.求叶节点个数
    3.求二叉树的高度
    4.交换二叉树的所有左右子树
    */
    int GetNodeNum(btnode *t)
    {
        if (t == nullptr)
            return 0;
        return GetNodeNum(t->left) + GetNodeNum(t->right) + 1;
    }
    int GetLeftNum(btnode *t)
    {
        if (t == nullptr)
            return 0;
        if (t->left == nullptr && t->right == nullptr)
            return 1;
        return GetLeftNum(t->left) + GetLeftNum(t->right);
    }
    int FindDepth(btnode *t)
    {
        if (t == nullptr)
            return 0;
        return max(FindDepth(t->left), FindDepth(t->right)) + 1;
    }
    void SwapLeftRight(btnode *t)
    {
        if (t == nullptr)
            return;
        swap(t->left, t->right);
        SwapLeftRight(t->left);
        SwapLeftRight(t->right);
    }
};
/*
    哈夫曼树编码/译码系统的实现
    实现哈夫曼树的创建 哈夫曼编码以及解码的实现
*/
class HuffmanTree
{
    ElementType element;
    int w;
    HuffmanTree *left, *right;
    bool operator<(const HuffmanTree &t) const
    {
        return w < t.w;
    }

public:
    HuffmanTree *CreatHuffmanTree(vector<HuffmanTree *> &v)
    {
        priority_queue<HuffmanTree *, vector<HuffmanTree *>, greater<HuffmanTree *>> pq;
        for (auto i : v)
        {
            pq.push(i);
        }
        while (pq.size() > 1)
        {
            auto t1 = pq.top();
            pq.pop();
            auto t2 = pq.top();
            pq.pop();
            auto t = new HuffmanTree;
            t->w = t1->w + t2->w;
            t->left = t1;
            t->right = t2;
            pq.push(t);
        }
        return pq.top();
    }
    void Code(HuffmanTree *t, string s)
    {
        if (t == nullptr)
            return;
        if (t->left == nullptr && t->right == nullptr)
        {
            cout << t->element << " " << s << endl;
            return;
        }
        Code(t->left, s + "0");
        Code(t->right, s + "1");
    }
    void Decode(HuffmanTree *t, string s)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '0')
            {
                if (t->left == nullptr)
                {
                    cout << "error";
                    return;
                }
                t = t->left;
            }
            else
            {
                if (t->right == nullptr)
                {
                    cout << "error";
                    return;
                }
                t = t->right;
            }
            if (t->left == nullptr && t->right == nullptr)
            {
                cout << t->element << endl;
            }
        }
    }
};