#include <bits/stdc++.h>

// 比较 直接插入排序 ， 简单选择排序， 冒泡排序，快速排序，两路合并排序，堆排序
// 最好时间复杂度

/*
直接插入排序（Insertion Sort）：

最好情况时间复杂度：O(n)，当输入数组已经有序时。
最坏情况时间复杂度：O(n^2)，当输入数组逆序排列时。
平均情况时间复杂度：O(n^2)。

简单选择排序（Selection Sort）：

最好情况时间复杂度：O(n^2)，无论输入数组的顺序如何，每次都需要进行完整的比较和交换。
最坏情况时间复杂度：O(n^2)。
平均情况时间复杂度：O(n^2)。

冒泡排序（Bubble Sort）：

最好情况时间复杂度：O(n)，当输入数组已经有序时，通过优化可达到线性时间复杂度。
最坏情况时间复杂度：O(n^2)。
平均情况时间复杂度：O(n^2)。

快速排序（Quick Sort）：

最好情况时间复杂度：O(n log n)，当每次划分都能均匀地将数组分成两部分时。
最坏情况时间复杂度：O(n^2)，当输入数组已经有序或逆序排列时，每次划分只能得到一个元素和剩余的元素。
平均情况时间复杂度：O(n log n)。

两路合并排序（Merge Sort）：

最好情况时间复杂度：O(n log n)。
最坏情况时间复杂度：O(n log n)。
平均情况时间复杂度：O(n log n)。

堆排序（Heap Sort）：

最好情况时间复杂度：O(n log n)。
最坏情况时间复杂度：O(n log n)。
平均情况时间复杂度：O(n log n)。
*/
/*
空间复杂度
直接插入排序（Insertion Sort）：

空间复杂度：O(1)，原地排序算法，只需要常数级别的额外空间。
简单选择排序（Selection Sort）：

空间复杂度：O(1)，原地排序算法，只需要常数级别的额外空间。
冒泡排序（Bubble Sort）：

空间复杂度：O(1)，原地排序算法，只需要常数级别的额外空间。
快速排序（Quick Sort）：

空间复杂度：取决于具体实现方式。
在经典的快速排序中，空间复杂度为O(log n)，主要用于递归调用时的栈空间。
在优化的快速排序实现中，如三路快排或使用尾递归优化，空间复杂度可以降低为O(1)或O(log n)。
两路合并排序（Merge Sort）：

空间复杂度：O(n)，需要额外的辅助数组来进行归并操作。
堆排序（Heap Sort）：

空间复杂度：O(1)，原地排序算法，只需要常数级别的额外空间。
*/

/*
直接插入排序（Insertion Sort）：

稳定性：稳定排序算法。相同元素的相对顺序不会改变。
简单选择排序（Selection Sort）：

稳定性：不稳定排序算法。相同元素的相对顺序可能会改变。
冒泡排序（Bubble Sort）：

稳定性：稳定排序算法。相同元素的相对顺序不会改变。
快速排序（Quick Sort）：

稳定性：不稳定排序算法。由于快速排序使用分治的思想，元素的交换可能导致相同元素的相对顺序发生改变。
两路合并排序（Merge Sort）：

稳定性：稳定排序算法。在归并过程中，相同元素会按照原始顺序放入结果数组。
堆排序（Heap Sort）：

稳定性：不稳定排序算法。堆排序的过程中会进行元素的交换，可能导致相同元素的相对顺序发生改变。
*/

/*
哪些算法可以提前确定元素最终有序位置?
直接插入排序（Insertion Sort）：在插入每个元素时，通过比较确定元素的最终有序位置。

冒泡排序（Bubble Sort）：每次冒泡过程中，如果没有发生交换，则说明数组已经有序，可以提前结束排序。

快速排序（Quick Sort）：通过选择一个基准元素，将数组分为两部分，左边的元素都小于基准元素，右边的元素都大于基准元素。递归地对两个子数组进行快速排序，而不需要再对已经有序的子数组进行排序。

两路合并排序（Merge Sort）：在归并过程中，如果当前元素的值等于下一个元素的值，则可以提前确定它们的相对顺序，将它们按照原始顺序放入结果数组。
*/

// Q1 设计算法求出关键字最小的K个元素
std::vector<int> findKMin(std::vector<int> arr, int k)
{
    std::vector<int> res;
    std::priority_queue<int> q;
    for (int i = 0; i < arr.size(); i++)
    {
        q.push(arr[i]);
        if (q.size() > k)
            q.pop();
    }
    while (!q.empty())
    {
        res.push_back(q.top());
        q.pop();
    }
    return res;
}
struct LinkNode
{
    int data;
    LinkNode *next;
    LinkNode(int x) : data(x), next(nullptr) {}
};
// 实现一个基于链表的简单选择排序
void selectSort(LinkNode *head)
{
    LinkNode *p = head->next;
    while (p)
    {
        LinkNode *min = p;
        LinkNode *q = p->next;
        while (q)
        {
            if (q->data < min->data)
                min = q;
            q = q->next;
        }
        std::swap(p->data, min->data);
        p = p->next;
    }
}
// 实现一个直接插入排序
void insertSort(LinkNode *head)
{
    LinkNode *p = head->next;
    while (p)
    {
        LinkNode *q = head;
        while (q != p)
        {
            if (q->data > p->data)
                std::swap(q->data, p->data);
            q = q->next;
        }
        p = p->next;
    }
}
