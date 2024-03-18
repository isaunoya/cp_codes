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

void solve() {
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];
  vc<vi> g(n);
  rep(i, n - 1) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }

  ll ans = 0;
  vc<ll> f(n);
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    vc<ll> F;
    for (auto v : g[u])
      if (v == p)
        continue;
      else {
        dfs(dfs, v, u);
        F.pb(f[v]);
      }

    sort(all(F)), reverse(all(F));

    f[u] = a[u];
    if (F.size() >= 1)
      cmax(f[u], a[u] + F[0]);
    if (F.size() >= 2)
      cmax(f[u], F[0] + F[1]);
    if (F.size() >= 3) {
      cmax(f[u], a[u] + F[0] + F[1] + F[2]);
      ll cur = F[0] + F[1] + F[2];
      rep(i, 3, sz(F)) {
        cur += F[i];
        cmax(f[u], a[u] + cur);
      }
    }
    cmax(ans, f[u]);

    f[u] = a[u];
    if (F.size() >= 1)
      cmax(f[u], F[0]);
    if (F.size() >= 2) {
      ll cur = F[0] + F[1];
      cmax(f[u], a[u] + cur);
      rep(i, 2, sz(F)) {
        cur += F[i];
        cmax(f[u], a[u] + cur);
      }
    }
  };

  dfs(dfs, 0, -1);

  cout << ans << "\n";
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