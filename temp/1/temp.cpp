#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
using namespace std;
using ll = long long;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<ll> b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<int> stk;
  vector<int> l(n, -1);
  vector<int> r(n, -1);
  for (int i = 0; i < n; i++) {
    while (!stk.empty() && a[stk.back()] > a[i]) {
      l[i] = stk.back();
      stk.pop_back();
    }
    if (!stk.empty()) {
      r[stk.back()] = i;
    }
    stk.emplace_back(i);
  }
  int root = stk[0];
  auto dfs = [&](auto &self, int u) -> array<ll, 4> {
    if (u == -1) {
      return array<ll, 4>{0LL, 0LL, 0LL, 0LL};
    }
    auto L = self(self, l[u]);
    auto R = self(self, r[u]);
    auto dp = array<ll, 4>{L[1] + b[u] + R[2],
                           max({L[1], 0LL}) + max({b[u] + R[3], 0LL}),
                           max({L[3] + b[u], 0LL}) + max({R[2], 0LL}),
                           max({L[2] + b[u] + R[1], L[2] + b[u], b[u] + R[1],
                                L[2], R[1], L[3] + b[u] + R[3], L[3] + b[u],
                                b[u] + R[3], L[3], R[3], b[u], 0LL})};
    dp[1] = max(dp[1], dp[0]);
    dp[2] = max(dp[2], dp[0]);
    dp[3] = max(dp[3], dp[0]);
    return dp;
  };

  cout << dfs(dfs, root)[0] << "\n";
}

/*
u = minimum(L...R)
return b[u] + max{solve(L, l < u) + solve(r > u, R)};
*/