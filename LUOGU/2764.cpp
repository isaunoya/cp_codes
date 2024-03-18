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
template <typename BS> struct BipartiteMatching_Dense {
  int N1, N2;
  vector<BS> &adj;
  vector<int> match_1, match_2;
  vector<int> que;
  vector<int> prev;
  BS vis;
  BipartiteMatching_Dense(vector<BS> &adj, int N1, int N2)
      : N1(N1), N2(N2), adj(adj), match_1(N1, -1), match_2(N2, -1) {
    for (int s = 0; s < N1; s++)
      bfs(s);
  }
  void bfs(int s) {
    if (match_1[s] != -1)
      return;
    que.resize(N1), prev.resize(N1);
    int l = 0, r = 0;
    vis.set(), prev[s] = -1;
    que[r++] = s;
    while (l < r) {
      int u = que[l++];
      BS cand = vis & adj[u];
      for (int v = cand._Find_first(); v < N2; v = cand._Find_next(v)) {
        vis[v] = 0;
        if (match_2[v] != -1) {
          que[r++] = match_2[v];
          prev[match_2[v]] = u;
          continue;
        }
        int a = u, b = v;
        while (a != -1) {
          int t = match_1[a];
          match_1[a] = b, match_2[b] = a, a = prev[a], b = t;
        }
        return;
      }
    }
    return;
  }
  vector<pair<int, int>> matching() {
    vector<pair<int, int>> res;
    for (int v = 0; v < N1; v++)
      if (match_1[v] != -1)
        res.pb(v, match_1[v]);
    return res;
  }
  pair<vector<int>, vector<int>> vertex_cover() {
    vector<int> que(N1);
    int l = 0, r = 0;
    vis.set();
    vector<bool> done(N1);
    for (int i = 0; i < N1; i++) {
      if (match_1[i] == -1)
        done[i] = 1, que[r++] = i;
    }
    while (l < r) {
      int a = que[l++];
      BS cand = adj[a] & vis;
      for (int b = cand._Find_first(); b < N2; b = cand._Find_next(b)) {
        vis[b] = 0;
        int to = match_2[b];
        assert(to != -1);
        if (!done[to])
          done[to] = 1, que[r++] = to;
      }
    }
    vector<int> left, right;
    for (int i = 0; i < N1; i++)
      if (!done[i])
        left.pb(i);
    for (int i = 0; i < N2; i++)
      if (!vis[i])
        right.pb(i);
    return {left, right};
  }
};
using bs = bitset<150>;
void solve() {
  int N, M;
  read(N, M);
  vc<bs> adj(N);
  while (M--) {
    int a, b;
    read(a, b);
    --a, --b;
    adj[a][b] = 1;
  }
  BipartiteMatching_Dense<bs> bm(adj, N, N);
  auto pairs = bm.matching();
  vi deg(N);
  vc<vi> g(N);
  for (auto [x, y] : pairs) {
    g[x].pb(y);
    deg[y] += 1;
  }

  vi vis(N);
  auto find = [&](auto self, int u) ->void {
    vis[u] = 1;
    cout << u + 1 << " ";
    for (auto v : g[u]) {
      deg[v] -= 1;
      self(self, v);
    }
  };

  int cnt = 0;
  rep(i, N) {
    if (!deg[i] && !vis[i]) {
      find(find, i);
      cout << "\n";
      cnt += 1;
    }
  }
  cout << cnt << "\n";
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