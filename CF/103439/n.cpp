#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (auto i = 0; i < a; i++)
#define rep2(i, a) for (auto i = 0; i < a; i++)
#define rep3(i, a, b) for (auto i = a; i < b; i++)
#define rep4(i, a, b, c) for (auto i = a; i < b; i += c)
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

const int B = 500;
const int N = 2e5 + 5;
ll dp[2][N];
int vis[2][N];

void solve() {
  int m;
  cin >> m;
  // debug(m);
  int n = m * 2;
  vc<pii> a(n);
  rep(i, n) {
    int x, y;
    cin >> x >> y;
    if (x > y)
      swap(x, y);
    a[i] = pii(x, y);
  }
  // debug(a);
  shuffle(all(a), rng);
  memset(vis, -1, sizeof vis);
  memset(dp, 0xcf, sizeof dp);
  int p = 0, q = 1;

  dp[0][0] = 0, vis[0][0] = 0;
  rep(i, n) {
    // debug(p,q);
    int L = i / 2 - B;
    int R = i / 2 + B;
    cmax(L, 0);
    cmin(R, m+1);
    rep(j, L, R + 1) dp[q][j] = -lnf;
    rep(j, L, R) {
      if (vis[p][j] == i) {
        // debug(i,j);
        vis[q][j] = i + 1;
        cmax(dp[q][j], dp[p][j] + a[i].se);
        vis[q][j + 1] = i + 1;
        cmax(dp[q][j + 1], dp[p][j] - a[i].fi);
      }
    }
    p ^= 1, q ^= 1;
  }

  cout << dp[p][m] << "\n";
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