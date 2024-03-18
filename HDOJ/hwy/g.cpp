#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

const int P = 998244353;
void md(int &x) {
  if (x >= P)
    x -= P;
}
void solve() {
  int n;
  cin >> n;
  vc<vi> g(n);
  rp(i, n - 1) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].pb(b);
    g[b].pb(a);
  }
  vi s(n);
  vector tmp(5, vi(n + 1));
  vector f(5, vc<vi>(n, vi(n + 1)));
  auto dfs = [&](auto &self, int u, int p) -> void {
    s[u] = f[0][u][0] = 1;
    for (auto v : g[u]) {
      if (v == p) {
        continue;
      }
      self(self, v, u);
      rp(i, 5) rp(j, n + 1) tmp[i][j] = 0;
      rp(a, 5) rp(b, 5) {
        if (a && b) {
          continue;
        }
        rp(i, s[u] + 1) {
          rp(j, s[v] + 1) {
            md(tmp[a + b][i + j] += 1ll * f[a][u][i] * f[b][v][j] % P);
          }
        }
      }
      s[u] += s[v];
      rp(a, 5) rp(i, s[u] + 1) f[a][u][i] = tmp[a][i];
    }
    rp(i, 5) rp(j, n + 1) tmp[i][j] = 0;
    rp(a, 5) rp(i, s[u] + 1) {
      if (i - 1 >= 0)
        md(tmp[a][i - 1] += (ll)f[a][u][i] * i % P);
      if (i + 1 <= n)
        md(tmp[a][i + 1] += f[a][u][i]);
      if (a < 4)
        md(tmp[a + 1][i] += f[a][u][i]);
    }
    rp(a, 5) rp(i, s[u] + 1) f[a][u][i] = tmp[a][i];
  };
  dfs(dfs, 0, -1);
  // debug(f[0][0][0], f[4][0][0]);
  cout << f[0][0][0] << " " << f[4][0][0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}