#include <bits/stdc++.h>
using namespace std;

int matrix[100][100];
using pii = pair<int, int>;
// Q1
void init(vector<pii> edge)
{
    vector<int> deg(100, 0);
    for (auto e : edge)
    {
        matrix[e.first][e.second] = 1;
        deg[e.second]++;
    }
    vector<pii> ans;
    // 强联通分量
    for (int i = 0; i < 100; i++)
    {
        for (int j = i + 1; j < 100; j++)
        {
            if (matrix[i][j] == 1 && matrix[j][i] == 1)
            {
                ans.push_back({i, j});
            }
        }
    }
}
// Q2 Q3 同Q1

// Q10
void dfs(vector<vector<int>> &adj_matrix, int node, vector<bool> &visited, vector<vector<int>> &tree)
{
    visited[node] = true;
    for (int i = 0; i < adj_matrix.size(); i++)
    {
        if (adj_matrix[node][i] && !visited[i])
        {
            visited[i] = true;
            tree[node].push_back(i);
            dfs(adj_matrix, i, visited, tree);
        }
    }
}

vector<vector<int>> generate_tree(vector<vector<int>> &adj_matrix)
{
    int n = adj_matrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> tree(n);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(adj_matrix, i, visited, tree);
        }
    }
    return tree;
}

// Q15 给出所有拓扑排序序列
vector<string> ans;
void dfs(vector<vector<int>> &adj_matrix, vector<int> &in_degree, vector<int> &path)
{
    bool flag = false;
    for (int i = 0; i < in_degree.size(); i++)
    {
        if (in_degree[i] == 0)
        {
            flag = true;
            path.push_back(i);
            in_degree[i]--;
            for (int j = 0; j < adj_matrix.size(); j++)
            {
                if (adj_matrix[i][j])
                {
                    in_degree[j]--;
                }
            }
            dfs(adj_matrix, in_degree, path);
            path.pop_back();
            in_degree[i]++;
            for (int j = 0; j < adj_matrix.size(); j++)
            {
                if (adj_matrix[i][j])
                {
                    in_degree[j]++;
                }
            }
        }
    }
    if (!flag)
    {
        string s;
        for (int i = 0; i < path.size(); i++)
        {
            s += to_string(path[i]);
        }
        ans.push_back(s);
    }
}

// Q18 Prim 最小生成树
void prim(vector<vector<int>> graph)
{
    int n = graph.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    vector<bool> visited(n, false);
    q.push({0, 0});
    int ans = 0;
    vector<int> res;
    while (!q.empty())
    {
        auto p = q.top();
        q.pop();
        if (visited[p.second])
            continue;
        res.push_back(p.second);
        visited[p.second] = true;
        ans += p.first;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && graph[p.second][i])
            {
                q.push({graph[p.second][i], i});
            }
        }
    }
}
// Q19
void kruscal(vector<vector<int>> graph)
{
    int n = graph.size();
    vector<int> parent(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;
    auto find = [&](int x)
    {
        while (x != parent[x])
            x = parent[x];
        return x;
    };
    auto merge = [&](int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
            parent[fx] = fy;
    };
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; i++)
        {
            if (graph[i][j])
            {
                edges.push_back({graph[i][j], {i, j}});
            }
        }
    }
    sort(edges.begin(), edges.end());
    int ans = 0;
    vector<int> res;
    for (auto e : edges)
    {
        int w = e.first;
        int x = e.second.first;
        int y = e.second.second;
        if (find(x) != find(y))
        {
            merge(x, y);
            ans += w;
            res.push_back(w);
        }
    }
}
// Q21 dijkstra求以1为源点，到其他所有点的最短路径
void dijkstra(vector<vector<int>> graph)
{
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 1});
    dist[1] = 0;
    visited[1] = true;
    while (!q.empty())
    {
        auto p = q.top();
        q.pop();
        int u = p.second;
        if (visited[u])
            continue;
        visited[u] = true;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && graph[u][i] && dist[i] > dist[u] + graph[u][i])
            {
                dist[i] = dist[u] + graph[u][i];
                q.push({dist[i], i});
            }
        }
    }
}
