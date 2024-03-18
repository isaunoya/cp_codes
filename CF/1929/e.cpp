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
const int P = 998244353;

void convolution_or(vector<int> &f, int e) {
  int n = 1 << e;
  for (int j = 0; j < e; j++) {
    for (int i = 0; i < n; i++) {
      if (i >> j & 1) {
        f[i] += f[i ^ 1 << j];
        if (f[i] >= P) {
          f[i] -= P;
        }
      }
    }
  }
}
void envolution_or(vector<int> &f, int e) {
  int n = 1 << e;
  for (int j = 0; j < e; j++) {
    for (int i = 0; i < n; i++) {
      if (i >> j & 1) {
        f[i] -= f[i ^ 1 << j];
        if (f[i] < 0) {
          f[i] += P;
        }
      }
    }
  }
}

void solve() {
  int n;
  cin >> n;
  vc<vi> g(n);
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    g[a].pb(b);
    g[b].pb(a);
  }
  vi w(n);
  int k;
  cin >> k;
  rep(i, k) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    w[a] ^= 1 << i;
    w[b] ^= 1 << i;
  }
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    for (auto v : g[u])
      if (v != p) {
        dfs(dfs, v, u);
        w[u] ^= w[v];
      }
  };
  dfs(dfs, 0, -1);

  int K = 1 << k;
  vi f(K);
  rep(i, 1, n) { f[w[i]] = rng() % P; }
  vi F = f;
  convolution_or(F, k);
  vi G = F, e = f;
  for (int i = 1; i <= k; i++) {
    e = G;
    envolution_or(e, k);
    if (e.back()) {
      cout << i << "\n";
      return;
    }

    for (int j = 0; j < (1 << k); j++) {
      G[j] = 1ll * G[j] * F[j] % P;
    }
  }
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