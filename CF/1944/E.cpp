#if defined(LOCAL)
#include <D:/cp/templates/my_template_compiled.hpp>
#else
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#define debug(...) 42
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
template <typename T> using vc = vector<T>;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second
#endif

void solve() {
  int N;
  cin >> N;
  vc<vi> g(N);
  rep(i, N - 1) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].pb(y);
    g[y].pb(x);
  }
  vi p(N, -1);
  auto get = [&](int x) {
    vi d(N, -1), q{x};
    d[x] = 0;
    rep(q.size()) {
      int u = q[i];
      for (auto v : g[u])
        if (d[v] == -1)
          q.pb(v), d[v] = d[u] + 1, p[v] = u;
    }
    return d;
  };
  auto cur = get(0);
  int r1 = max_element(all(cur)) - begin(cur);
  cur = get(r1);
  int r2 = max_element(all(cur)) - begin(cur);
  int mxd = cur[r2];
  vc<pii> ans;
  if (mxd % 4 != 3) {
    int u = r2;
    rep(i, mxd / 2) u = p[u];
    for (int i = 0; i <= (mxd + 1) / 2; i++) {
      ans.pb(u, i);
    }
  } else {
    int u = r2;
    rep(i, mxd / 2) u = p[u];
    int v = p[u];
    int w = mxd / 2;
    for (int i = 1; i <= w; i += 2)
      ans.pb(u, i), ans.pb(v, i);
  }
  cout << sz(ans) << "\n";
  for (auto [x, d] : ans) {
    cout << x + 1 << " " << d << "\n";
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