#include <bits/stdc++.h>

using namespace std;

const int P = 998244353;
const int N = 1005;
unordered_map<int, int> dp[N];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    dp[i].clear();
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[y].push_back(x);
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    auto dfs = [&](auto &dfs, int u, int val) -> int {
      if (!val)
        return 0;
      if (dp[u].count(val)) {
        return dp[u][val];
      }
      int res = 1;
      for (auto v : g[u]) {
        res += dfs(dfs, v, val / a[v]);
        if (res >= P) {
          res -= P;
        }
      }
      return dp[u][val] = res;
    };
    ans += dfs(dfs, i, k / a[i]);
    if (ans >= P) {
      ans -= P;
    }
  }
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}