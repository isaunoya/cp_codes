#include <bits/stdc++.h>
using namespace std;
const int K = 1e7 + 5;
bool appear[K];
const int N = 1e4 + 5;
int stk[N], top1, stk2[N], top2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    --x;
    --y;
    e[x].emplace_back(y, w);
    e[y].emplace_back(x, w);
  }
  vector<int> goal(m);
  vector<bool> ok(m);
  for (int i = 0; i < m; i++) {
    cin >> goal[i];
  }
  vector<bool> vis(n, false);
  vector<int> sz(n);
  int tot = n, rt = -1;
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    sz[u] = 1;
    int mx = 0;
    for (auto [v, w] : e[u])
      if (v != p && !vis[v]) {
        dfs(dfs, v, u);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
      }
    mx = max(mx, tot - sz[u]);
    if (mx * 2 <= tot) {
      rt = u;
    }
  };
  auto getd = [&](auto &getd, int u, int p, int d) -> void {
    if (vis[u]) {
      return;
    }
    stk2[top2++] = d;
    for (auto [v, w] : e[u]) {
      if (v != p) {
        getd(getd, v, u, d + w);
      }
    }
  };

  appear[0] = 1;
  auto doit = [&](int u) {
    top1 = top2 = 0;
    for (auto [v, w] : e[u]) {
      if (vis[v]) {
        continue;
      }
      top2 = 0;
      getd(getd, v, u, w);
      for (int i = 0; i < m; i++) {
        if (ok[i])
          continue;
        for (int j = 0; j < top2; j++) {
          if (goal[i] >= stk2[j] && appear[goal[i] - stk2[j]]) {
            ok[i] = 1;
            break;
          }
        }
      }
      for (int i = 0; i < top2; i++) {
        if (stk2[i] >= K) {
          continue;
        }
        stk[top1++] = stk2[i];
        appear[stk2[i]] = 1;
      }
    }
    while (top1--)
      appear[stk[top1]] = 0;
  };

  auto solve = [&](auto &solve, int u) -> void {
    vis[u] = 1;
    doit(u);
    for (auto [v, w] : e[u]) {
      if (vis[v]) {
        continue;
      } else {
        tot = sz[v];
        rt = -1;
        dfs(dfs, v, u);
        solve(solve, rt);
      }
    }
  };

  tot = n;
  rt = -1;
  dfs(dfs, rt, -1);
  solve(solve, rt);
  for (int i = 0; i < m; i++) {
    if (ok[i]) {
      cout << "AYE"
           << "\n";
    } else {
      cout << "NAY"
           << "\n";
    }
  }
}