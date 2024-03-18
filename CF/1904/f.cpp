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
#define all(x) begin(x), end(x)
#define fi first
#define se second

struct HLD {
  HLD() {}
  vector<vector<int>> G;
  int n;
  vector<int> dfn, sz, son, top, d, fa;
  int idx;
  void dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : G[u])
      if (v != p) {
        fa[v] = u;
        d[v] = d[u] + 1;
        dfs(v, u), sz[u] += sz[v];
        if (son[u] == -1 || sz[v] > sz[son[u]])
          son[u] = v;
      }
  }
  void dfs2(int u, int t) {
    top[u] = t, dfn[u] = idx++;
    if (son[u] != -1)
      dfs2(son[u], t);
    for (auto v : G[u])
      if (top[v] == -1)
        dfs2(v, v);
  }
  HLD(const vector<vector<int>> &g, const int &root = 0) {
    n = g.size();
    G = g;
    sz.resize(n);
    dfn.resize(n);
    son.resize(n, -1);
    top.resize(n, -1);
    d.resize(n);
    fa.resize(n);
    dfs(root, -1), idx = 0, dfs2(root, root);
  }
  int lca(int x, int y) {
    while (top[x] != top[y]) {
      if (d[top[x]] < d[top[y]])
        swap(x, y);
      x = fa[top[x]];
    }
    return d[x] < d[y] ? x : y;
  }
  vector<pair<int, int>> chain(int x, int y) {
    assert(0 <= x && x < n);
    assert(0 <= y && y < n);
    vector<pair<int, int>> L, R;
    while (top[x] != top[y]) {
      assert(0 <= x && x < n);
      assert(0 <= y && y < n);
      if (d[top[x]] > d[top[y]]) {
        L.emplace_back(dfn[x], dfn[top[x]]);
        x = fa[top[x]];
      } else {
        R.emplace_back(dfn[top[y]], dfn[y]);
        y = fa[top[y]];
      }
    }
    L.emplace_back(dfn[x], dfn[y]);
    reverse(R.begin(), R.end());
    L.insert(L.end(), R.begin(), R.end());
    return L;
  }
};

const int N = 262144;
vector<int> G[N * 3];
int in[N * 2], out[N * 2], cnt, deg[N * 3];
void add_edge(int x, int y) { G[x].push_back(y), deg[y] += 1; }
void init() {
  cnt = N;
  for (int i = 0; i < N; i++)
    in[i + N] = out[i + N] = i;
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

void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> g(n);
  rep(i, n - 1) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }

  HLD f(g);
  vi dfn(n);
  for (int i = 0; i < n; i++)
    dfn[i] = f.dfn[i];
  vi rev(n);
  rep(i, n) rev[dfn[i]] = i;
  init();
  rep(i, m) {
    int t, a, b, c;
    cin >> t >> a >> b >> c;
    --a, --b, --c;
    if (t == 1) {
      auto segs = f.chain(a, b);
      for (auto [x, y] : segs) {
        if (x > y)
          swap(x, y);
        // for(int i=x;i<=y;i++)if(i!=dfn[c])add_edge(dfn[c],i);
        if (x <= dfn[c] && dfn[c] <= y) {
          if (x <= dfn[c] - 1) {
            auto v = link_range(x, dfn[c] - 1);
            for (auto node : v) {
              add_edge(dfn[c], node);
            }
          }
          if (dfn[c] + 1 <= y) {
            auto v = link_range(dfn[c] + 1, y);
            for (auto node : v) {
              add_edge(dfn[c], node);
            }
          }
        } else {
          auto v = link_range(x, y);
          for (auto node : v) {
            add_edge(dfn[c], node);
          }
        }
      }
    } else {
      auto segs = f.chain(a, b);
      for (auto [x, y] : segs) {
        if (x > y)
          swap(x, y);
        // for(int i=x;i<=y;i++)if(i!=dfn[c])add_edge(i,dfn[c]);
        if (x <= dfn[c] && dfn[c] <= y) {
          if (x <= dfn[c] - 1) {
            auto v = range_link(x, dfn[c] - 1);
            for (auto node : v) {
              add_edge(node, dfn[c]);
            }
          }
          if (dfn[c] + 1 <= y) {
            auto v = range_link(dfn[c] + 1, y);
            for (auto node : v) {
              add_edge(node, dfn[c]);
            }
          }
        } else {
          auto v = range_link(x, y);
          for (auto node : v) {
            add_edge(node, dfn[c]);
          }
        }
      }
    }
  }

  queue<int> q;
  rep(i, N * 3) if (!deg[i]) q.emplace(i);
  vi ord;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u < n) {
      ord.push_back(rev[u]);
    }
    for (auto v : G[u])
      if (--deg[v] == 0)
        q.emplace(v);
  }
  if (int(ord.size()) < n) {
    cout << -1 << "\n";
    return;
  } else {
    vi rk(n, -1);
    rep(i, n) rk[ord[i]] = i;
    rep(i, n) cout << rk[i] + 1 << " \n"[i + 1 == n];
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