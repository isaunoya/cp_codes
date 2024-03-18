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
  int n, m;
  cin >> n >> m;
  vc<vc<pii>> g(n);
  rep(i, m) {
    int x;
    cin >> x;
    while (x--) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      g[u].pb(v, i);
      g[v].pb(u, i);
    }
  }
  int q;
  cin >> q;
  vi a(q);
  vc<set<int>> s(m);
  rep(i, q) {
    cin >> a[i];
    --a[i];
    s[a[i]].insert(i);
  }
  rep(i, m) {
    s[i].insert(q + 1);
  }
  vi d(n, q + 1);
  d[0] = 0;
  pqg<pii> pq;
  pq.emplace(0, 0);
  vi vis(n);
  for (int i = 0; i < q; i++) {
    while (!pq.empty() && pq.top().fi == i) {
      auto [dd, u] = pq.top();
      debug(dd, u + 1);
      pq.pop();
      if (vis[u]) continue;
      vis[u] = 1;
      for (auto [v, c] : g[u]) {
        if (d[v] > *s[c].begin() + 1) {
          pq.emplace(d[v] = *s[c].begin() + 1, v);
        }
      }
    }
    s[a[i]].erase(i);
  }
  if (d.back() == q + 1) {
    cout << -1 << "\n";
  } else {
    cout << d.back() << "\n";
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