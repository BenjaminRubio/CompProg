#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

struct SA
{
    int n; vector<int> C, R, R_, sa, sa_, lcp;
    inline int gr(int i) { return i < n ? R[i] : 0; }
    void csort(int maxv, int k)
    {
        C.assign(maxv + 1, 0); rep(i, n) C[gr(i + k)]++;
        repx(i, 1, maxv + 1) C[i] += C[i - 1];
        for (int i = (int)n - 1; i >= 0; i--) sa_[--C[gr(sa[i] + k)]] = sa[i];
        sa.swap(sa_);
    }
    void getSA(vector<int>& s)
    {
        R = R_ = sa = sa_ = vector<int>(n); rep(i, n) sa[i] = i;
        sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });
        int r = R[sa[0]] = 1;
        repx(i, 1, n) R[sa[i]] = (s[sa[i]] != s[sa[i - 1]]) ? ++r : r;
        for (int h = 1; h < n && r < n; h <<= 1)
        {
            csort(r, h); csort(r, 0); r = R_[sa[0]] = 1;
            repx(i, 1, n)
            {
                if (R[sa[i]] != R[sa[i - 1]] || gr(sa[i] + h) != gr(sa[i - 1] + h)) r++;
                R_[sa[i]] = r;
            } R.swap(R_);
        }
    }
    void getLCP(vector<int>& s)
    {
        lcp.assign(n, 0); int k = 0;
        rep(i, n)
        {
            int r = R[i] - 1;
            if (r == n - 1) { k = 0; continue; }
            int j = sa[r + 1];
            while (i + k < n && j + k < n and s[i + k] == s[j + k]) k++;
            lcp[r] = k; if (k) k--;
        }
    }
    SA(vector<int>& s) { n = s.size(); getSA(s); getLCP(s); }
};

int T;
string S;

int main()
{
    cin >> T;
    while (T--)
    {
        cin >> S; int N = S.size();

        vector<int> a; for (char c : S) a.push_back(c);
        SA sa(a);

        int i;
        rep(j, N) if (sa.sa[j] == 0) { i = j; break; }

        long long ans = 0, p = 1e6;
        for (int j = i; j < N; j++) p = min((long long)sa.lcp[j], p), ans += p;

        p = 1e6;
        for (int j = i - 1; j >= 0; j--) p = min((long long)sa.lcp[j], p), ans += p;

        cout << ans + N << '\n';
    }
}
