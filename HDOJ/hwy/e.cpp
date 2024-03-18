#include <bits/stdc++.h>
#include <cstdio>
#ifndef LOCAL
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> g(n + m);
  vi deg(n + m);

  auto add = [&](int u, int v) {
    deg[u] += 1;
    g[v].pb(u);
  };

  rp(i, n) {
    int u = i;
    int k;
    cin >> k;
    while (k--) {
      int v;
      cin >> v;
      v += n;
      add(u, v);
    }
  }
  rp(i, m) {
    int u = i + n;
    int k;
    cin >> k;
    while (k--) {
      int v;
      cin >> v;
      add(u, v);
    }
  }

  auto ok = [&](int u) { return u < n; };

  vi no(n + m, 0);
  auto solve = [&](int s) {
    vi dp(n + m, -1);
    vi vis(n + m, 0);
    vi d = deg;
    queue<int> q;
    dp[s] = ok(s);
    q.emplace(s);
    vis[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : g[u]) {
        vis[v] = 1;
        --d[v];
        if (dp[v] != -1)
          continue;
        if (dp[u] == 0)
          dp[v] = 1;
        if (d[v] == 0 && dp[u] == 1) {
          dp[v] = 0;
        }
        if (dp[v] != -1) {
          q.emplace(v);
        }
      }
    }
    rp(i, n + m) {
      if (!vis[i])
        return 0;
      if (ok(i) && dp[i] == 0)
        no[i] = 1;
      if (!ok(i) && dp[i] == 1)
        no[i] = 1;
      if (dp[i] == -1)
        no[i] = 1;
    }
    return 1;
  };

  debug(deg);
  rp(i, n + m) {
    if (deg[i] == 0) {
      cout << "No\n";
      return;
    }
  }
  rp(i, n + m) {
    if (!solve(i)) {
      cout << "No\n";
      return;
    }
  }
  rp(i, n + m) {
    if (!no[i]) {
      cout << "Yes\n";
      return;
    }
  }

  cout << "No\n";
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