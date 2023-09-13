#include <bits/stdc++.h>

// Q1 判断线性表是否是有序表
bool isSorted(std::vector<int> arr)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

// Q2 对有序表进行对半搜索

int binarySearch(std::vector<int> arr, int target)
{
    int l = 0, r = arr.size() - 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

//长度 log2(11)