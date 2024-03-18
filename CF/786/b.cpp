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

struct SEG_EDGE {
  SEG_EDGE() {}
  int N;
  vector<vector<int>> G;

  void add_edge(int x, int y) { G[x].push_back(y); }
  vector<int> in, out;
  SEG_EDGE(int n) {
    N = n;
    in.resize(N * 2);
    out.resize(N * 2);
    G.resize(N * 3);
    for (int i = 0; i < N; i++)
      in[i + N] = out[i + N] = i;
    int cnt = N;
    for (int i = N - 1; i >= 1; i--)
      in[i] = cnt++, add_edge(in[i], in[i * 2]), add_edge(in[i], in[i * 2 + 1]);
    for (int i = N - 1; i >= 1; i--)
      out[i] = cnt++, add_edge(out[i * 2], out[i]),
      add_edge(out[i * 2 + 1], out[i]);
  }

  vector<int> link_range(int l, int r) { // [l, r]
    vector<int> Node;
    for (l += N, r += N + 1; l < r; l /= 2, r /= 2) {
      if (l & 1)
        Node.push_back(in[l++]);
      if (r & 1)
        Node.push_back(in[--r]);
    }
    return Node;
  }

  vector<int> range_link(int l, int r) { // [l, r]
    vector<int> Node;
    for (l += N, r += N + 1; l < r; l /= 2, r /= 2) {
      if (l & 1)
        Node.push_back(out[l++]);
      if (r & 1)
        Node.push_back(out[--r]);
    }
    return Node;
  }

  vector<vector<int>> get_all() { return G; }
};

void solve() {
  int n, q, s;
  cin >> n >> q >> s;
  --s;
  using pll = pair<ll, ll>;
  priority_queue<pll, vc<pll>, greater<pll>> Q;
  SEG_EDGE f(n);
  auto G = f.get_all();
  vc<vc<pii>> g(G.size());
  rep(i, G.size()) {
    for (auto j : G[i])
      g[i].pb(j, 0);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int v, u, w;
      cin >> v >> u >> w;
      --v, --u;
      g[v].pb(u, w);
    } else if (t == 2) {
      int v, l, r, w;
      cin >> v >> l >> r >> w;
      l--, r--;
      auto Node = f.link_range(l, r);
      --v;
      for (auto t : Node)
        g[v].pb(t, w);
    } else if (t == 3) {
      int v, l, r, w;
      cin >> v >> l >> r >> w;
      l--, r--;
      auto Node = f.range_link(l, r);
      --v;
      for (auto t : Node)
        g[t].pb(v, w);
    }
  }
  int N = G.size();
  vc<ll> dis(N, lnf);
  Q.emplace(dis[s] = 0, s);
  vi vis(N);
  while (!Q.empty()) {
    auto [d, u] = Q.top();
    Q.pop();
    if (vis[u])
      continue;
    vis[u] = 1;
    for (auto [v, w] : g[u]) {
      if (d + w < dis[v])
        Q.emplace(dis[v] = d + w, v);
    }
  }
  rep(i, n) if (dis[i] == lnf) dis[i] = -1;
  rep(i, n) cout << dis[i] << " \n"[i + 1 == n];
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