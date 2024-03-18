#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (int i = 0; i < a; i++)
#define rep2(i, a) for (int i = 0; i < a; i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define pb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  x = x < y ? x : y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  x = x > y ? x : y;
}
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

int n, m, k;
const int N = 33;
vi g[N], a;
int c[N], id[N];
double dp[N][N][1 << 12];

// 没被摧毁且没看见 1
// 否则 0

double solve(int x, int y, int mask) {
  if (!mask)
    return 0;
  if (dp[x][y][mask] != -lnf) {
    return dp[x][y][mask];
  }
  double &ans = dp[x][y][mask] = 0;
  for (auto v : g[x]) {
    int ii = id[v];
    int msk = mask;
    double res = 0;
    if (ii != -1) {
      if (msk >> ii & 1) {
        msk ^= 1 << ii;
        res += a[ii];
      }
    }
    int ms = 0;
    rep(i, k) {
      if (msk >> i & 1) {
        res += 1ll * 1. / (n - y) * solve(v, y + 1, msk ^ (1 << i));
        ms++;
      }
    }
    if (n - ms - y > 0) {
      res += 1. * (n - ms - y) * 1. / (n - y) * solve(v, y + 1, msk);
    }
    cmax(ans, res);
  }
  return ans;
}

void solve() {
  cin >> n >> m >> k;
  rep(i, m) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }
  int bas = 0;
  rep(i, k) {
    int x;
    cin >> x;
    --x;
    if (x == 0)
      bas++;
    else
      c[x]++;
  }
  rep(i, n) {
    id[i] = -1;
    if (c[i])
      a.pb(c[i]), id[i] = a.size() - 1;
  }
  k = a.size();
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      rep(l, 1 << 12) dp[i][j][l] = -lnf;
  double ans = bas + solve(0, 0, (1 << k) - 1);

  cout << fixed << setprecision(10);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}