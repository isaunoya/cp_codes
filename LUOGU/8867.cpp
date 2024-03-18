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
struct two_edge_connected_components {
  vector<int> tcc;
  int cnt = 0;
  two_edge_connected_components(vector<vector<int>> &E) {
    int N = E.size();
    vector<int> p(N, -1);
    vector<int> d(N, -1);
    vector<int> imos(N, 0);
    for (int i = 0; i < N; i++) {
      if (p[i] == -1) {
        d[i] = 0;
        dfs1(E, p, d, imos, i);
      }
    }
    tcc = vector<int>(N, -1);
    for (int i = 0; i < N; i++) {
      if (tcc[i] == -1) {
        tcc[i] = cnt;
        cnt++;
        dfs2(E, p, imos, i);
      }
    }
  }
  void dfs1(vector<vector<int>> &E, vector<int> &p, vector<int> &d,
            vector<int> &imos, int v = 0) {
    bool pe = false;
    for (int w : E[v]) {
      if (w != p[v] || pe) {
        if (d[w] == -1) {
          p[w] = v;
          d[w] = d[v] + 1;
          dfs1(E, p, d, imos, w);
          imos[v] += imos[w];
        } else if (d[w] < d[v]) {
          imos[v]++;
          imos[w]--;
        }
      } else {
        pe = true;
      }
    }
  }
  void dfs2(vector<vector<int>> &E, vector<int> &p, vector<int> &imos,
            int v = 0) {
    for (int w : E[v]) {
      if (tcc[w] == -1) {
        if (imos[w] > 0) {
          tcc[w] = tcc[v];
        } else {
          tcc[w] = cnt;
          cnt++;
        }
        dfs2(E, p, imos, w);
      }
    }
  }
  int operator[](int v) { return tcc[v]; }
};

const int P = 1e9 + 7;
const int N = 2e6;
int pw[N];
void md(int &x) {
  if (x >= P) {
    x -= P;
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> e(n);
  rep(i, m) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    e[u].pb(v);
    e[v].pb(u);
  }

  two_edge_connected_components tcc(e);
  int k = tcc.cnt;
  vc<vi> g(k);
  vi ver(k), edge(k), ae(k);
  rep(i, n) {
    ver[tcc[i]] += 1;
    for (auto j : e[i]) {
      if (tcc[i] != tcc[j]) {
        g[tcc[i]].pb(tcc[j]);
      } else {
        int pos = tcc[i];
        edge[pos] += 1;
      }
    }
  }
  rep(i, k) edge[i] /= 2;
  int ans = 0;
  vc<array<int, 2>> dp(k);
  auto dfs = [&](auto self, int u, int p) -> void {
    ae[u] = edge[u];
    dp[u][0] = pw[edge[u]];
    dp[u][1] = pw[ver[u] + edge[u]] - dp[u][0];
    md(dp[u][1] += P);
    for (auto v : g[u]) {
      if (v == p) {
        continue;
      }
      self(self, v, u);
      ae[u] += ae[v] + 1;
      int t = dp[u][1], nt = 0;
      md(nt += 2ll * t * dp[v][0] % P);
      md(nt += 1ll * t * dp[v][1] % P);
      md(nt += 1ll * dp[u][0] * dp[v][1] % P);
      dp[u][1] = nt;
      dp[u][0] = 2ll * dp[u][0] * dp[v][0] % P;
    }
    if (u == 0) {
      md(ans += dp[u][1]);
    } else {
      md(ans += 1ll * dp[u][1] * pw[m - ae[u] - 1] % P);
    }
  };
  dfs(dfs, 0, -1);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  pw[0] = 1;
  rep(i, 1, N) md(pw[i] = pw[i - 1] * 2);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}