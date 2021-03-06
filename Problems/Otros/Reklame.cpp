#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> par;
typedef vector<int> vi;
typedef vector<float> vfloat;
typedef vector<par> vp;
typedef vector<vi> graph;
typedef vector<vp> wgraph;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = a; i < (int)b; i++)
#define invrep(i, a, b) for (int i = a; i > (int)b; i--)

#define pb push_back
#define pf push_front
#define eb emplace_back
#define ppb pop_back

#define umap unordered_map

#define lg(x) (31 - __buitlin_clz(x))
#define lgg(x) (63 - __buitlin_clzll(x))
#define gcd __gcd

//ios::sync_with_stdio(0); cin.tie(0);
//cout.setf(ios::fixed); cout.precision(4);

#define debugx(x) // cerr << #x << ": " << x << endl
#define debugv(v)         \
    cerr << #v << ":";    \
    for (auto e : v)      \
        cerr << " " << e; \
    cerr << endl
#define debugm(m)                                        \
    cerr << #m << endl;                                  \
    rep(i, (int)m.size())                                \
    {                                                    \
        cerr << i << ":";                                \
        rep(j, (int)m[i].size()) cerr << " " << m[i][j]; \
        cerr << endl;                                    \
    }
#define debugmp(m) //                                                                       \
    cerr << #m << endl;                                                                         \
    rep(i, (int)m.size())                                                                       \
    {                                                                                           \
        cerr << i << ":";                                                                       \
        rep(j, (int)m[i].size()) cerr << " {" << m[i][j].first << "," << m[i][j].second << "}"; \
        cerr << endl;                                                                           \
    }
#define print(x) copy(x.begin(), x.end(), ostream_iterator<int>(cout, “”)), cout << endl

int n, k, r, d_;
graph d;
graph DP;

int dp(int id, int b)
{
    // cerr << "IN: " << id << ' ' << b << '\n';
    if (id >= n)
    {
        int m = 0;
        rep(i, 7)
        {
            if (d[id - 1][i])
                m = i;
        }
        return m + 1;
    }

    if (DP[id][b] != -1)
        return DP[id][b];

    int ans = 1e9;
    rep(i, 7)
    {
        // cerr << "i: " << i << '\n';
        bool able = true;
        rep(j, 7)
        {
            // cerr << "j: " << j << ' ' << ((b >> (2 * (i + j))) & 3) << '\n';
            if (d[id][j] && ((b >> (2 * (i + j))) & 3) == k)
                able = false;
        }
        // cerr << "able: " << able << '\n';
        if (able)
        {
            int b_ = 0;
            rep(j, 7)
            {
                if (d[id][j])
                    b_ |= (((b >> (2 * (i + j))) & 3) + 1) << (2 * j);
                else
                    b_ |= ((b >> (2 * (i + j))) & 3) << (2 * j);
            }
            ans = min(ans, i + dp(id + 1, b_));
        }
    }
    return DP[id][b] = ans;
}

int main()
{
    cin >> n >> k;
    d.assign(n, vi(7, 0));
    rep(i, n)
    {
        cin >> r;
        d[i][0] = 1;
        rep(j, r - 1)
        {
            cin >> d_;
            d[i][d_ - 1] = 1;
        }
    }
    DP.assign(n, vi(1 << 21, -1));

    cout << dp(0, 0) << '\n';
}