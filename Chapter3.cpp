#include <bits/stdc++.h>

// Q1
//  中缀表达式转后缀表达式
using string = std::string;
string trans(string &s)
{
    std::stack<char> op;
    string ans;
    std::unordered_map<char, int> mp;
    mp['+'] = 2;
    mp['-'] = 2;
    mp['*'] = 3;
    mp['/'] = 3;
    mp['^'] = 1;

    for (auto c : s)
    {
        if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9')
        {
            ans += c;
        }
        else
        {
            int weight = mp[c];
            if (op.empty() || c == '(')
            {
                op.push(c);
            }
            else if (c == ')')
            {
                while (op.top() != '(')
                {
                    ans += op.top();
                    op.pop();
                }
                op.pop();
            }
            else
            {
                while (!op.empty() && op.top() != '(' && weight <= mp[op.top()])
                {
                    ans += op.top();
                    op.pop();
                }
                op.push(c);
            }
        }
    }
    while (!op.empty())
    {
        auto c = op.top();
        op.pop();
        ans += c;
    }
    return ans;
}

// Q2
// 设A,B,C,D,E五个元素依次进栈，问能否得到以下序列。
// 1. A,B,C,D,E
// 2. A,C,E,B,D
// 3. C,A,B,D,E
// 4. E,D,C,B,A

void solve(string s)
{
    std::stack<char> st;
    int idx = 0;
    std::vector<char> push_ans;
    std::vector<char> pop_ans;
    for (auto c : s)
    {
        if (st.empty() || st.top() < c)
        {
            while (idx <= c - 'A')
            {
                st.push(idx + 'A');
                push_ans.push_back(idx + 'A');
                idx++;
            }
        }
        if (st.top() == c)
        {
            st.pop();
            pop_ans.push_back(c);
        }
        else if (st.top() > c)
        {
            std::cout << "No Such Order" << std::endl;
            return;
        }
    }
    std::cout << "Push order: " << std::endl;
    for (auto c : push_ans)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    std::cout << "Pop order: " << std::endl;
    for (auto c : pop_ans)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}
// Q3
// 设计一个递归算法，实现在一个线性表中搜索一个指定关键字值的元素
struct SeqList
{
    int *data;
    int length;
};
void find(int index, int key, SeqList &list)
{
    if (index == list.length)
    {
        std::cout << "Not Found" << std::endl;
        return;
    }
    if (list.data[index] == key)
    {
        std::cout << "Found at index: " << index << std::endl;
        return;
    }
    find(index + 1, key, list);
}

int main()
{
    std::vector<string> ss;
    ss.push_back("(a+b)/(c+d)");
    ss.push_back("b^2-4*a*c");
    ss.push_back("a*b-b/c^2");
    ss.push_back("(a+b)*c+d/(e+f)");
    ss.push_back("(a+b)*(c*d+e)-a*c");

    // 展示了Q1的答案
    for (auto &v : ss)
    {

        std::cout << trans(v) << std::endl;
    }
    solve("CABDE");
}