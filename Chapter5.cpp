#include <bits/stdc++.h>

// Q1 A,B,C可以有多少无序树，有序树，二叉树
// 无序树：7种
// 有序树：8种
// 二叉树：6种(这里仅代表节点数=3)

// Q2 假设一棵二叉树的层次遍历序列为A,中序遍历序列为B.请给出这棵二叉树
using string = std::string;
struct node
{
  char data;
  node *left, *right;
};
std::map<char, node *> mp;
node *solve(string A, string B)
{
  if (A.size() == 0)
    return nullptr;
  auto root = mp[A[0]];
  int pos = B.find(A[0]);

  root->left = solve(A.substr(1, pos), B.substr(0, pos));
  root->right = solve(A.substr(pos + 1), B.substr(pos + 1));
  return root;
}

// Q3 (1) Maxlength = 5 , MinLength = 4
//(2) 5

// Q4 给定一个序列S和权重W，请构造出一棵哈夫曼树
typedef struct HNode
{
  int weight;
  HNode *lchild, *rchild;
  char data;
} *Htree;

Htree createHuffmanTree(std::vector<char> s, std::vector<int> arr, int n)
{
  Htree forest[100010];
  Htree root = NULL;
  for (int i = 0; i < n; i++)
  {
    Htree temp;
    temp = (Htree)malloc(sizeof(HNode));
    temp->weight = arr[i];
    temp->lchild = temp->rchild = NULL;
    temp->data = s[i];
    forest[i] = temp;
  }

  for (int i = 1; i < n; i++)
  {
    int minn = -1, minnSub;
    for (int j = 0; j < n; j++)
    {
      if (forest[j] != NULL && minn == -1)
      {
        minn = j;
        continue;
      }
      if (forest[j] != NULL)
      {
        minnSub = j;
        break;
      }
    }

    for (int j = minnSub; j < n; j++)
    {
      if (forest[j] != NULL)
      {
        if (forest[j]->weight < forest[minn]->weight)
        {
          minnSub = minn;
          minn = j;
        }
        else if (forest[j]->weight < forest[minnSub]->weight)
        {
          minnSub = j;
        }
      }
    }

    // 建新树
    root = (Htree)malloc(sizeof(HNode));
    root->weight = forest[minn]->weight + forest[minnSub]->weight;
    root->lchild = forest[minn];
    root->rchild = forest[minnSub];

    forest[minn] = root;
    forest[minnSub] = NULL;
  }
  return root;
}

int getWPL(Htree root, int len)
{
  if (root == NULL)
    return 0;
  else
  {
    if (root->lchild == NULL && root->rchild == NULL)
      return root->weight * len;
    else
    {
      int left = getWPL(root->lchild, len + 1);
      int right = getWPL(root->rchild, len + 1);
      return left + right;
    }
  }
}
void huffmanCoding(Htree root, int len, int arr[])
{
  if (root != NULL)
  {
    if (root->lchild == NULL && root->rchild == NULL)
    {
      printf("The encode of weight %d  =", root->weight);
      for (int i = 0; i < len; i++)
        printf("%d", arr[i]);
      printf("\n");
    }
    else
    {
      arr[len] = 0;
      huffmanCoding(root->lchild, len + 1, arr);
      arr[len] = 1;
      huffmanCoding(root->rchild, len + 1, arr);
    }
  }
}
int main()
{
  std::vector<char> s = {'a', 'b', 'c', 'd', 'e'};
  std::vector<int> w = {35, 25, 15, 15, 10};
  auto head = createHuffmanTree(s, w, 5);
  huffmanCoding(head, 0, new int[100]());
}
// Q5
struct BinaryNode
{
  int data;
  BinaryNode *left, *right;
};
int getDepth(BinaryNode *root)
{
  if (root == nullptr)
    return 0;
  return std::max(getDepth(root->left), getDepth(root->right)) + 1;
}
// 判断是否为完全二叉树
bool check(BinaryNode *root)
{
  if (root == nullptr)
    return true;
  std::queue<BinaryNode *> q;
  q.push(root);
  bool flag = false;
  while (!q.empty())
  {
    auto node = q.front();
    q.pop();
    if (node->left)
    {
      if (flag)
        return false;
      q.push(node->left);
    }
    else
      flag = true;
    if (node->right)
    {
      if (flag)
        return false;
      q.push(node->right);
    }
    else
      flag = true;
  }
  return true;
}
// 求解内路径长度
int getInternalPathLength(BinaryNode *root, int depth)
{
  if (root == nullptr)
    return 0;
  return depth + getInternalPathLength(root->left, depth + 1) + getInternalPathLength(root->right, depth + 1);
}
// 求解外路径长度
int getExternalPathLength(BinaryNode *root, int depth)
{
  if (root == nullptr)
    return 0;
  if (root->left == nullptr && root->right == nullptr)
    return depth;
  return getExternalPathLength(root->left, depth + 1) + getExternalPathLength(root->right, depth + 1);
}
