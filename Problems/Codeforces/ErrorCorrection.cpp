#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

class Hopcroft
{
    vector<vector<int>> g;
    vector<int> U, dist;
    int inf = 1e9;

    bool bfs() {
        queue<int> q;
        for (int u : U) if (match[u] == nil) dist[u] = 0, q.push(u);
        else dist[u] = inf;
        dist[nil] = inf;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u != nil) for (int v : g[u]) if (dist[match[v]] == inf)
            {
                dist[match[v]] = dist[u] + 1;
                q.push(match[v]);
            }
        }
        return (dist[nil] != inf);
    }

    bool dfs(int u) {
        if (u == nil)
            return true;
        for (int v : g[u]) if (dist[match[v]] == dist[u]+1 and dfs(match[v]))
        {
            match[v] = u, match[u] = v;
            return true;
        }
        dist[u] = inf;
        return false;
    }

public:
    vector<int> match;
    int nil, isPerfect, matchSize = 0;

    // gg is a bidirectional graph, UU has the nodes in the left partition
    Hopcroft(vector<vector<int>> &gg, vector<int> &UU) 
    {
        g = gg; U = UU; nil = g.size();
        match.assign(g.size() + 1, nil);
        dist.assign(g.size() + 1, inf);
        while (bfs()) for (int u : U) if (match[u] == nil and dfs(u))
            matchSize++;
        isPerfect = (matchSize == U.size() and g.size() == U.size() * 2);
    }
};

int N, sz;
vector<string> S;
vector<vector<int>> G;
vector<int> L;
int M[27];

void get_parity(int i)
{
    string s = S[i];
    vector<bool> V(sz, 0);

    int ans = 0;
    rep(j, sz) if (!V[j])
    {
        int k = j, cnt = 1; V[k] = 1;
        while (!V[M[S[i][k] - 'a']]) { k = M[S[i][k] - 'a']; V[k] = 1; cnt++; }
        ans += (cnt - 1) % 2;
    } ans %= 2;

    if (ans) L.push_back(i);
}

int main()
{
    cin >> N;

    S.resize(N);
    rep(i, N) cin >> S[i];

    sz = S[0].size();
    rep(i, sz) M[S[0][i] - 'a'] = i;

    rep(i, N) get_parity(i);

    G.assign(N, {});
    rep(i, N) repx(j, i + 1, N)
    {
        int cnt = 0;
        rep(k, sz) if (S[i][k] != S[j][k]) cnt++;

        if (cnt == 2)
        {
            G[i].push_back(j);
            G[j].push_back(i);
        }
    }

    Hopcroft H(G, L);

    cout << max(H.matchSize, N - H.matchSize) << '\n';
}