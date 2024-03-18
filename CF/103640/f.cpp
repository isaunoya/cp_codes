#include <algorithm>
#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
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

template <class... T> void read() {}
template <class T> void read(T &x) { cin >> x; }
template <class T, class S> void read(pair<T, S> &v) {
  read(v.first, v.second);
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> g(n);
  rep(i, 0, m) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }
  vi vis(n);
  vis[n - 1] = 1;

  vector<int> list;
  auto dfs = [&](auto &self, int u) -> int {
    if (vis[u]) {
      return -1;
    }
    list.push_back(u);
    vis[u] = 1;
    int mx = u;
    for (auto v : g[u]) {
      mx = max(mx, self(self, v));
    }
    return mx;
  };

  vc<vi> f;
  vi gg;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      list.clear();
      int mx = dfs(dfs, i);
      f.pb(list);
      gg.pb(mx);
    }
  }
  int t = max_element(all(gg)) - gg.begin();
  vi ans(n);
  for (int i : f[t]) {
    ans[i] = 1;
  }
  for (auto x : ans) {
    cout << char(x + 'A');
  }
  cout << "\n";
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