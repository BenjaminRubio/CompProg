#include <bits/stdc++.h>
using namespace std;

struct SA
{
    int sz, l; vector<int> L, Lk;
    vector<map<char, int>> N;

    SA(string s)
    {
        int n = s.size();
        L.resize(2 * n), Lk.resize(2 * n); N.resize(2 * n);
        l = L[0] = 0, Lk[0] = -1, sz = 1;
        for (char c : s) extend(c);
    }
    void extend(char c)
    {
        int cur = sz++, p = l; L[cur] = L[l] + 1;
        while (p != -1 && !N[p].count(c)) N[p][c] = cur, p = Lk[p];
        if (p == -1) Lk[cur] = 0;
        else
        {
            int q = N[p][c];
            if (L[p] + 1 == L[q]) Lk[cur] = q;
            else
            {
                int w = sz++;
                L[w] = L[p] + 1, Lk[w] = Lk[q], N[w] = N[q];
                while (p != -1 && N[p][c] == q) N[p][c] = w, p = Lk[p];
                Lk[q] = Lk[cur] = w;
            }
        }
        l = cur;
    }
};