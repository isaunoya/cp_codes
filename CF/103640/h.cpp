#include <bits/stdc++.h>

using namespace std;

#define int long long
#define endl '\n'

#define PII pair<int, int>
#define fi first
#define se second

const int N = 507, INF = 1e9 + 7, NPOS = -1;
struct Matrix
{
    int n;
    int a[N][N];
};
struct KuhnMunkres : Matrix
{
    int hl[N], hr[N], slk[N];
    int fl[N], fr[N], vl[N], vr[N], pre[N], q[N], ql, qr;
    int check(int i)
    {
        if (vl[i] = 1, fl[i] != NPOS)
            return vr[q[qr++] = fl[i]] = 1;
        while (i != NPOS)
            swap(i, fr[fl[i] = pre[i]]);
        return 0;
    }
    void bfs(int s)
    {
        fill(slk, slk + n, INF), fill(vl, vl + n, 0), fill(vr, vr + n, 0);
        for (vr[q[ql = 0] = s] = qr = 1;;)
        {
            for (int d; ql < qr;)
                for (int i = 0, j = q[ql++]; i < n; ++i)
                    if (!vl[i] && slk[i] >= (d = hl[i] + hr[j] - a[i][j]))
                        if (pre[i] = j, d)
                            slk[i] = d;
                        else if (!check(i))
                            return;
            int d = INF;
            for (int i = 0; i < n; ++i)
                if (!vl[i] && d > slk[i])
                    d = slk[i];
            for (int i = 0; i < n; ++i)
            {
                if (vl[i])
                    hl[i] += d;
                else
                    slk[i] -= d;
                if (vr[i])
                    hr[i] -= d;
            }
            for (int i = 0; i < n; ++i)
                if (!vl[i] && !slk[i] && !check(i))
                    return;
        }
    }
    void ask()
    {
        fill(fl, fl + n, NPOS), fill(fr, fr + n, NPOS), fill(hr, hr + n, 0);
        for (int i = 0; i < n; ++i)
            hl[i] = *max_element(a[i], a[i] + n);
        for (int j = 0; j < n; ++j)
            bfs(j);
    }
} km;
struct Istream
{
    char b[20 << 20], *i, *e;
    Istream(FILE *in) : i(b), e(b + fread(b, sizeof(*b), sizeof(b) - 1, in)) {}
    Istream &operator>>(int &val)
    {
        // return val=strtoll(i,&i,10),*this;
        while (*i < '0')
            ++i;
        for (val = 0; *i >= '0'; ++i)
            val = (val << 3) + (val << 1) + (*i - '0');
        return *this;
    }
} kin(stdin);
#define cin kin

const int INF2 = 2e9;
void solve()
{
  int N;
  cin >> N;
  int a[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < N; i += 2) {
    for (int j = 0; j < N; j += 2) {
      int L = j - 1;
      int R = j + 1;
      int val = 0;
      if (L >= 0) {
        val += a[i][L];
      }
      if (R < N) {
        val += a[i][R];
      }
      km.a[i / 2 + 1][j / 2 + 1] = INF2 - val;
    }
  }
    km.n = (N + 1) / 2 + 2, km.ask();
    long long ans = 0;
    for (int i = 1; i <= (N + 1) / 2 + 2; ++i)
        ans += km.a[i][km.fl[i]];
    cout << INF2 * ((N + 1) / 2) - ans << '\n';
    // for (int i = 1; i <= (N + 1) / 2; ++i)
    //     cout << (km.a[i][km.fl[i]] ? km.fl[i] : 0) << ' ';
}

signed main()
{
    solve();
}