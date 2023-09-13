#include <bits/stdc++.h>

struct SeqList
{
    int *data;
    int MaxSize;
    int n;
};

// Q1
// 编写程序实现对顺序表的逆置
void reverse(SeqList sql)
{
    int n = sql.n;
    auto data = sql.data;
    for (int i = 0; i < n / 2; i++)
    {
        std::swap(data[i], data[n - i - 1]);
    }
}

// Q2
// 编写程序实现对单链表的逆置

struct Node
{
    int data;
    Node *next;
};

Node *Head;
void reverse(Node *head, Node *prev)
{
    if (head->next == nullptr)
    {
        Head = head;
        head->next = prev;
        return;
    }
    reverse(head->next, head);
    head->next = prev;
}

// Q3
// 将两个有序递增的单链表合并为一个递减的单链表

Node *merge(Node *head1, Node *head2)
{
    Node *head = new Node;
    Node *p = head;
    while (head1 != nullptr && head2 != nullptr)
    {
        if (head1->data < head2->data)
        {
            p->next = head1;
            head1 = head1->next;
        }
        else
        {
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    while (head1 != nullptr)
    {
        p->next = head1;
        head1 = head1->next;
        p = p->next;
    }
    while (head2 != nullptr)
    {
        p->next = head2;
        head2 = head2->next;
        p = p->next;
    }
    return head->next;
}
