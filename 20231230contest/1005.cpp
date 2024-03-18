#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  vector<int> d(n);
  d[0] = 0;
  vector<int> dfn(n);
  int idx = 0;
  vector<int> sz(n);
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    dfn[u] = ++idx;
    sz[u] = 1;
    for (auto [v, w] : g[u])
      if (v != p) {
        d[v] = d[u] ^ w;
        dfs(dfs, v, u);
        sz[u] += sz[v];
      }
  };
  dfs(dfs, 0, -1);

  vector<array<int, 32>> t(n * 2);
  for (int i = 0; i < n * 2; i++)
    for (int j = 0; j < 32; j++)
      t[i][j] = 0;

  auto upd = [&](int i, int j) {
    for (i += n; i; i /= 2) {
      t[i][j] += 1;
    }
  };
  auto query = [&](int l, int r, int j) {
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        res += t[l++][j];
      if (r & 1)
        res += t[--r][j];
    }
    return res;
  };
  int q;
  cin >> q;
  vector<vector<pair<int, int>>> b(n), c(n);
  for (int i = 0; i < q; i++) {
    int l, r, x;
    cin >> l >> r >> x;
    --l;
    --r;
    --x;
    b[r].emplace_back(x, i);
    if (l > 0)
      c[l - 1].emplace_back(x, i);
  }
  vector<long long> ans(q);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 32; j++)
      if (d[i] >> j & 1)
        upd(i, j);
    for (auto [x, id] : b[i]) {
      for (int j = 0; j < 32; j++) {
        if (~d[x] >> j & 1) {
          ans[id] += 1ll * query(0, i + 1, j) * (1ll << j);
        } else {
          ans[id] += 1ll * (i + 1 - query(0, i + 1, j)) * (1ll << j);
        }
      }
    }
    for (auto [x, id] : c[i]) {
      for (int j = 0; j < 32; j++) {
        if (~d[x] >> j & 1) {
          ans[id] -= 1ll * query(0, i + 1, j) * (1ll << j);
        } else {
          ans[id] -= 1ll * (i + 1 - query(0, i + 1, j)) * (1ll << j);
        }
      }
    }
  }

  for (int i = 0; i < q; i++) {
    cout << ans[i] << "\n";
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}