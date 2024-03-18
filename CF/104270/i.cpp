#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
using namespace std;

using ll = long long;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  vector<array<ll, 3>> aa;
  for (int i = 0; i < n; i++)
    aa.emplace_back(array<ll, 3>{a[i], i, 0});
  for (int i = 0; i + 1 < n; i++)
    aa.emplace_back(array<ll, 3>{a[i] + a[i + 1], i, 1});
  sort(aa.begin(), aa.end());
  int L = 0;
  while ((1 << L) < n) {
    L += 1;
  }
  int N = 1 << L;
  vector<array<array<int, 2>, 2>> t(N * 2);
  for (int i = 0; i < n; i++)
    t[i + N][1][0] = 1;
  for (int i = n; i < N; i++) {
    t[i + N][0][0] = 1;
  }
  auto update = [&](int x) {
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        t[x][i][j] = 0;
        for (int k = 0; k < 2; k++)
          t[x][i][j] |= t[x * 2][i][k] & t[x * 2 + 1][k][j];
      }
  };
  for (int i = N; i < N + N; i++) {
    int x = i;
    while (x >>= 1) {
      update(x);
    }
  }
  auto upd = [&](int x, int c, bool k) {
    x += N;
    t[x][0][c] = k;
    while (x >>= 1)
      update(x);
  };
  int j = 0;
  ll mn = 2e18;
  for (int i = 0; i < n * 2 - 1; i++) {
    auto [v, x, c] = aa[i];
    upd(x, c, 1);
    while (t[1][0][0]) {
      auto [v2, x2, c2] = aa[j];
      mn = min(mn, v - v2);
      upd(x2, c2, 0);
      j += 1;
    }
  }
  cout << mn << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();

  return 0;
}