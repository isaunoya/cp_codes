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
#define all(x) begin(x), end(x)
#define fi first
#define se second

const int P = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  int r;
  cin >> r;
  --r;
  vc<vi> g(n);
  rep(i, n - 1) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    g[u].pb(v);
    g[v].pb(u);
  }
  vc<ll> fac(n + 1);
  fac[0] = 1;
  rep(i, 1, n + 1) fac[i] = fac[i - 1] * i % P;
  vi dfn(n), sz(n, 0);
  int c = 0;
  long long tmp = 0;
  long long ways = 1;
  auto dfs = [&](auto self, int u, int p) -> void {
    dfn[u] = c++;
    int son = 0;
    for (auto v : g[u]) {
      if (v == p)
        continue;
      self(self, v, u);
      tmp += 1ll * sz[u] * sz[v] % P;
      if (tmp >= P) {
        tmp -= P;
      }
      sz[u] += sz[v];
      son++;
    }
    sz[u] += 1;
    if (son > 0) {
      ways = ways * fac[son] % P;
    }
  };
  dfs(dfs, r, -1);
  vi t(n * 2);
  auto upd = [&](int x) {
    x += n;
    t[x] += 1;
    while (x >>= 1) {
      t[x] = t[x * 2] + t[x * 2 + 1];
    }
  };
  auto query = [&](int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        ans += t[l++];
      }
      if (r & 1) {
        ans += t[--r];
      }
    }
    return ans;
  };
  long long ans = 0;
  rep(i, n) {
    int l = dfn[i], r = dfn[i] + sz[i];
    ans += query(l, r);
    upd(l);
  }
  debug(ans, tmp, ways);
  tmp = tmp * ((P + 1) / 2) % P;
  cout << (ans + tmp) * ways % P << "\n";
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