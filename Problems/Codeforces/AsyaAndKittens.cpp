#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; i++)

struct DSU
{
    vector<int> p;
    DSU(int N) : p(N, -1) {}
    int get(int x) { return p[x] < 0 ? x : p[x] = get(p[x]); } 
    bool sameSet(int a, int b) { return get(a) == get(b); }
    int size(int x) { return -p[get(x)]; }
    void unite(int x, int y)
    {
        if ((x = get(x)) == (y = get(y))) return;
        if (p[x] > p[y]) swap(x,y);
        p[x] += p[y], p[y] = x;
    }
};

int N, a, b;
vector<int> P;
vector<vector<int>> G;

void dfs(int u)
{
    if (G[u].empty()) cout << u + 1 << ' ';
    for (int v : G[u]) dfs(v);
}

int main()
{
    cin >> N;

    G.resize(N + N - 1);
    P.resize(N); rep(i, N) P[i] = i;
    DSU dsu(N); int n = N;
    rep(i, N - 1)
    {
        cin >> a >> b; a--, b--;
        int x = P[dsu.get(a)], y = P[dsu.get(b)];
        dsu.unite(a, b); P[dsu.get(a)] = n;
        G[n].push_back(x), G[n].push_back(y); n++;
    }

    dfs(N + N - 2); cout << '\n';
}