#include <bits/stdc++.h>

// 散列表 线性探测法
struct HashTable
{
    int *elem;
    int mod = 11;
    int hash(int key)
    {
        return key % mod;
    }
    void init()
    {
        elem = new int[mod];
        for (int i = 0; i < mod; i++)
            elem[i] = -1;
    }
    void insert(int key)
    {
        int addr = hash(key);
        while (elem[addr] != -1)
            addr = (addr + 1) % mod;
        elem[addr] = key;
    }
};

// 散列表 二次探查法
struct HashTable2
{
    int *elem;
    int mod = 11;
    int hash(int key)
    {
        return key % mod;
    }
    void init()
    {
        elem = new int[mod];
        for (int i = 0; i < mod; i++)
            elem[i] = -1;
    }
    void insert(int key)
    {
        int addr = hash(key);
        int i = 1;
        while (elem[addr] != -1)
        {
            addr = (addr + i * i) % mod;
            i++;
        }
        elem[addr] = key;
    }
};
struct double_hashTable
{
    int *elem;
    int mod1 = 11;
    int mod2 = 7;
    using pii = std::pair<int, int>;
    int hash1(int key)
    {
        return key % mod1;
    }
    int hash2(int key)
    {
        return key % mod2 + 1;
    }
    void init()
    {
        elem = new int[mod1];
        for (int i = 0; i < mod1; i++)
            elem[i] = -1;
    }
    void insert(int key)
    {
        int addr = hash1(key);
        int i = 1;
        while (elem[addr] != -1)
        {
            addr = (addr + i * hash2(key)) % mod1;
            i++;
        }
        elem[addr] = key;
    }
};
