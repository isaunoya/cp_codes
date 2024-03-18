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
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    cin >> x;
}
template <class T, class S> void read(pair<T, S> &v) {
  cin >> v.first >> v.second;
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}


struct kosaraju {
  int n, c;
  vector<vector<int>> e1, e2;
  vector<bool> vis;
  kosaraju(vector<vector<int>> &e) {
    n = (int)e.size();
    e1 = e, e2.resize(n);
    rep(u, 0, n) for (auto v : e[u]) e2[v].emplace_back(u);
    vis.resize(n);
    scc.resize(n, -1);
    rep(i, 0, n) if (!vis[i]) dfs1(i);
    c = 0;
    for (auto i : r | views::reverse)
      if (scc[i] == -1)
        dfs2(i), c++;
  }
  vector<int> r;
  void dfs1(int u) {
    vis[u] = true;
    for (auto v : e1[u])
      if (!vis[v])
        dfs1(v);
    r.emplace_back(u);
  }
  vector<int> scc;
  void dfs2(int u) {
    scc[u] = c;
    for (auto v : e2[u])
      if (scc[v] == -1)
        dfs2(v);
  }
  const int &operator[](const int &x) { return scc[x]; }
};

void solve() {
  int n;
  cin >> n;
  vi a(n);
  vi c(n);
  read(a, c);
  rep(i, n){
    --a[i];
  }

  ll sum = 0;
  rep(i, n) {
    sum += c[i];
  }

  vc<vi> e(n);
  rep(i, n) {
    // debug(i, a[i]);
    e[i].pb(a[i]);
  }
  kosaraju k(e);

  int col = k.c;
  vc<ll> s(col);
  vc<pii> mn(col, make_pair(inf, inf));
  // debug(col);
  vi cnt(col);
  rep(i, n) {
    s[k[i]] += c[i];
    cmin(mn[k[i]], make_pair(c[i], i));
    cnt[k[i]] += 1;
  }

  rep(i, col) {
    if (cnt[i] == 1) {
      sum += s[i];
    } else {
      sum += s[i] - mn[i].first;
    }
  }

  vc<vi> g(col);
  vi deg(col);
  rep(u, n) {
    for (auto v : e[u]) {
      if (k[u] != k[v]) {
        g[k[u]].pb(k[v]);
        deg[k[v]]++;
      }
    }
  }

  vi tp;
  queue<int> q;
  rep(i, col) if (deg[i] == 0) {
    // debug(i);
    q.emplace(i);
  }
  while (!q.empty()) {
    int u = q.front();
    // debug(u);
    q.pop();
    tp.pb(u);
    for (auto v : g[u]) {
      if (--deg[v] == 0) {
        q.emplace(v);
      }
    }
  }

  // debug(tp);
  vi ans;
  for (auto c : tp) {
    int x = mn[c].second;
    if (cnt[c] == 1) {
      ans.pb(x);
    } else {
      int y = x;
      y = a[y];
      while (y != x) {
        ans.pb(y);
        y = a[y];
      }
      ans.pb(x);
    }
  }
  for (auto i : ans) {
    cout << i + 1 << " ";
  }
  cout << "\n";
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