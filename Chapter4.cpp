#include <bits/stdc++.h>

// Q1
// 给定一个稀疏矩阵，请给出行三元表和列三元表

void print(int **a, int m, int n)
{
    using a3 = std::array<int, 3>;
    std::vector<a3> row, col;
    for (int i = 0; i < m; ++i)
    {
        int cnt = 0;
        for (int j = 0; j < n; ++j)
        {
            if (a[i][j] != 0)
            {
                ++cnt;
                row.push_back({i, j, a[i][j]});
            }
        }
    }
    for (int j = 0; j < n; ++j)
    {
        int cnt = 0;
        for (int i = 0; i < m; ++i)
        {
            if (a[i][j] != 0)
            {
                ++cnt;
                col.push_back({i, j, a[i][j]});
            }
        }
    }
}

// Q2
//  稀疏矩阵快速转置算法
void tran(int **matrix, int m, int n)
{
    // 快速转置
    int num[m];
    int k[n];
    for (int i = 0; i < m; ++i)
    {
        num[i] = 0;
    }
    for (int i = 0; i < n; ++i)
    {
        k[i] = 0;
    }
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] != 0)
            {
                num[i]++;
            }
        }
    }
    k[0] = 0;
    for (int i = 1; i < n; i++)
    {
        k[i] = k[i - 1] + num[i - 1];
    }
}