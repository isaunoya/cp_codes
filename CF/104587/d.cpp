#include <bits/stdc++.h>
#include <numeric>
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

int dp[100][50][50];
void solve() {
  memset(dp, -1, sizeof dp);
  int r, s, n;
  cin >> r >> s >> n;
  vi a(r), b(s), c(n);
  rep(i, r) cin >> a[i];
  rep(i, s) cin >> b[i];
  rep(i, n) cin >> c[i];
  int A = accumulate(all(a), 0);
  int B = accumulate(all(b), 0);
  int m = *max_element(all(c));
  vi can(m + 1);
  can[0] = 1;
  rep(i, m + 1) {
    if (i >= A)
      can[i] |= can[i - A];
    if (i >= B)
      can[i] |= can[i - B];
  }
  vc<vi> ta(r, vi(r));
  vc<vi> tb(s, vi(s));
  rep(i, r) {
    ta[i][i] = 0;
    rep(j, r - 1) {
      int x = (i + j) % r;
      int nx = (i + j + 1) % r;
      ta[i][nx] = ta[i][x] + a[x];
    }
  }
  rep(i, s) {
    tb[i][i] = 0;
    rep(j, s - 1) {
      int x = (i + j) % s;
      int nx = (i + j + 1) % s;
      tb[i][nx] = tb[i][x] + b[x];
    }
  }
  auto dfs = [&](auto self, int i, int j, int k) {
    if (dp[i][j][k] != -1) {
      return dp[i][j][k];
    }
    if (i == n) {
      return 1;
    }
    rep(jj, r) {
      rep(kk, s) {
        if (c[i] >= ta[j][jj] + tb[k][kk] &&
            can[c[i] - ta[j][jj] - tb[k][kk]]) {
          if (self(self, i + 1, jj, kk))
            return dp[i][j][k] = 1;
        }
      }
    }
    return dp[i][j][k] = 0;
  };

  if (dfs(dfs, 0, 0, 0)) {
    cout << "yes\n";
  } else {
    cout << "no\n";
  }
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