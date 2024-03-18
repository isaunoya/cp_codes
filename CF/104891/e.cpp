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

void solve() {
  int n;
  cin >> n;
  vi a(n), b(n);
  rep(i, n) cin >> a[i], --a[i];
  rep(i, n) cin >> b[i], --b[i];
  vc<vi> g(n);
  vi stk;
  rep(i, n) {
    int x = a[i];
    while (!stk.empty() && stk.back() <= x) {
      stk.pop_back();
    }
    if (!stk.empty())
      g[stk.back()].pb(x);
    stk.pb(x);
  }
  stk.clear();
  rep(i, n) {
    int x = b[i];
    while (!stk.empty() && stk.back() >= x) {
      stk.pop_back();
    }
    if (!stk.empty())
      g[stk.back()].pb(x);
    stk.pb(x);
  }

  pq<int> p;
  pqg<int> q;
  vi _1, _2;
  vi deg(n);
  rep(u, n) for (auto v : g[u]) deg[v] += 1;
  auto deg2 = deg;
  rep(u, n) if (deg[u] == 0) p.emplace(u);
  while (!p.empty()) {
    int u = p.top();
    p.pop();
    _2.pb(u);
    for (auto v : g[u])
      if (--deg[v] == 0)
        p.emplace(v);
  }
  rep(u, n) if (deg2[u] == 0) q.emplace(u);
  while (!q.empty()) {
    int u = q.top();
    q.pop();
    _1.pb(u);
    for (auto v : g[u])
      if (--deg2[v] == 0)
        q.emplace(v);
  }
  if (_1 == a && _2 == b) {
    cout << "YES\n";
    int e = 0;
    rep(u, n) e += sz(g[u]);
    cout << e << "\n";
    rep(u, n) {
      for (auto v : g[u]) {
        cout << u + 1 << " " << v + 1 << "\n";
      }
    }
  } else {
    cout << "NO\n";
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