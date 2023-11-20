#include <bits/stdc++.h>
using namespace std;

/*
实验4 各种内排序算法的实现和性能比较
*/

#define KeyType int
#define DataType int
#define MAXSIZE 1000
struct entry
{
    KeyType key;
    DataType data;
};
struct List
{
    int n;
    entry D[MAXSIZE];
};

void SimpleSelectionSort(List &L)
{
    for (int i = 0; i < L.n; i++)
    {
        int k = i;
        for (int j = i + 1; j < L.n; j++)
        {
            if (L.D[j].key < L.D[k].key)
            {
                k = j;
            }
        }
        if (k != i)
        {
            swap(L.D[i], L.D[k]);
        }
    }
}
void DirectInsertionSort(List &L)
{
    for (int i = 1; i < L.n; i++)
    {
        if (L.D[i].key < L.D[i - 1].key)
        {
            entry tmp = L.D[i];
            int j;
            for (j = i - 1; j >= 0 && tmp.key < L.D[j].key; j--)
            {
                L.D[j + 1] = L.D[j];
            }
            L.D[j + 1] = tmp;
        }
    }
}
void BubbleSort(List &L)
{
    for (int i = 0; i < L.n - 1; i++)
    {
        bool flag = false;
        for (int j = 0; j < L.n - i - 1; j++)
        {
            if (L.D[j].key > L.D[j + 1].key)
            {
                swap(L.D[j], L.D[j + 1]);
                flag = true;
            }
        }
        if (!flag)
        {
            break;
        }
    }
}

void swap(struct entry *a, struct entry *b)
{
    struct entry temp = *a;
    *a = *b;
    *b = temp;
}
int partition(struct entry arr[], int low, int high)
{
    KeyType pivot = arr[high].key;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j].key < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(struct entry arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(struct entry arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct entry L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].key <= R[j].key)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct entry arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

vector<int> RandomMake(int n)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(0, 100000);
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        int x = dis(gen);
        ans.push_back(x);
    }
    return ans;
}

double TimeTest(void (*sort)(List &L), List &L, int n)
{
    clock_t start, end;
    start = clock();
    auto gen = RandomMake(n);
    for (int i = 0; i < n; i++)
    {
        L.D[i].key = gen[i];
    }
    sort(L);
    end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}
