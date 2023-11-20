#include <bits/stdc++.h>
using namespace std;

/*
实验3
1. 实现邻接矩阵的初始化 撤销 和边的搜索，插入，删除
*/

#define Elemtype int
class mGraph
{
    Elemtype **a;
    int n;
    int e;
    Elemtype noedge; // 无边标记
public:
    void init(int n, Elemtype noedge)
    {
        this->n = n;
        this->noedge = noedge;
        a = new Elemtype *[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = new Elemtype[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                a[i][j] = noedge;
            }
        }
    }
    void destroy()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] a[i];
        }
        delete[] a;
    }
    int Search(int i, int j)
    {
        if (a[i][j] != noedge)
        {
            // cout << "存在边" << endl;
            return a[i][j];
        }
        else
        {
            // cout << "不存在边" << endl;
            return noedge;
        }
    }
    void insert(int i, int j, Elemtype w)
    {
        if (a[i][j] == noedge)
        {
            a[i][j] = w;
            e++;
        }
    }
    void remove(int i, int j)
    {
        if (a[i][j] != noedge)
        {
            a[i][j] = noedge;
            e--;
        }
    }

    /*
    深度优先遍历 宽度优先遍历
    */
    void dfs(int v, bool *visited)
    {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < n; i++)
        {
            if (a[v][i] != noedge && !visited[i])
            {
                dfs(i, visited);
            }
        }
    }
    void bfs(int v, bool *visited)
    {
        queue<Elemtype> q;
        q.push(v);
        visited[v] = true;
        while (!q.empty())
        {
            Elemtype t = q.front();
            q.pop();
            cout << t << " ";
            for (int i = 0; i < n; i++)
            {
                if (a[t][i] != noedge && !visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }
};

/*
    邻接表的初始化 撤销 和边的搜索，插入，删除
*/
class eNode
{
public:
    int adjvex;
    Elemtype w;
    eNode *next;

    eNode(int adjvex, Elemtype w, eNode *next)
    {
        this->adjvex = adjvex;
        this->w = w;
        this->next = next;
    }
};
class lGraph
{
    int n;
    int e;
    eNode **a;

public:
    void init(int n, Elemtype noedge)
    {
        this->n = n;
        this->e = 0;
        a = new eNode *[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = nullptr;
        }
    }
    void destroy()
    {
        for (int i = 0; i < n; i++)
        {
            while (a[i] != nullptr)
            {
                auto p = a[i];
                a[i] = a[i]->next;
                delete p;
            }
        }
        delete[] a;
    }
    bool exist(int u, int v)
    {
        while (a[u] != nullptr)
        {
            if (a[u]->adjvex == v)
                return true;
            a[u] = a[u]->next;
        }
        return false;
    }
    void insert(int u, int v, Elemtype w)
    {
        if (u == v || u < 0 || v < 0 || u >= n || v >= n)
            return;
        if (exist(u, v))
            return;
        auto p = new eNode(v, w, a[u]);
        a[u] = p;
        e++;
    }
    void del(int u, int v)
    {
        if (!exist(u, v))
            return;
        auto p = a[u];
        eNode *last = nullptr;
        while (p->adjvex != v)
        {
            last = p;
            p = p->next;
        }
        auto q = p->next;
        if (last == nullptr)
        {
            a[u] = q;
        }
        else
        {
            last->next = q;
        }
    }
    /*
        邻接表 深度优先遍历 宽度优先遍历
    */
    void dfs(int u, bool *visited)
    {
        visited[u] = true;
        cout << u << " ";
        auto p = a[u];
        while (p != nullptr)
        {
            if (!visited[p->adjvex])
            {
                dfs(p->adjvex, visited);
            }
            p = p->next;
        }
    }
    void bfs(int u, bool *visited)
    {
        queue<int> q;
        q.push(u);
        visited[u] = true;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            cout << t << " ";
            auto p = a[t];
            while (p != nullptr)
            {
                if (!visited[p->adjvex])
                {
                    q.push(p->adjvex);
                    visited[p->adjvex] = true;
                }
                p = p->next;
            }
        }
    }
    /*
        智能交通中的最佳路径选择
    */
    int dijkstra(int s, int t)
    {
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        // 代价 编号
        pq.push({0, s});
        int *dis = new int[n+1];
        for (int i = 0; i < n; i++)
        {
            dis[i] = INT_MAX;
        }
        while (pq.size())
        {
            auto u = pq.top();
            pq.pop();
            if (u.second == t)
            {
                return u.first;
            }
            if(u.first > dis[u.second])
                continue;
            dis[u.second] = u.first;
            auto p = a[u.second];
            while (p != nullptr)
            {
                if (p->w + u.first < dis[p->adjvex])
                    pq.push({u.first + p->w, p->adjvex});
                p = p->next;
            }
        }
        return -1;
    }
};
