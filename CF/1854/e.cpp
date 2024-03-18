#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define per(i, x, y) for (int i = x; i > y; i--)
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  if (x > y)
    x = y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  if (x < y)
    x = y;
}
using ll = long long;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
void f(vector<long long> &F, int v) {
  for (int i = 60; i >= v; i--)
    F[i] += F[i - v];
}
void solve() {
  long long m;
  cin >> m;
  while (true) {
    vector<int> ans;
    vector<long long> F(61, 0);
    F[0] = 1;
    while (true) {
      int x = rng() % 6 + 1;
      auto NF = F;
      f(NF, x);
      if (NF[60] > m) {
        break;
      }
      ans.emplace_back(x);
      f(F, x);
    }
    while (F[60] < m) {
      int p = 0;
      rep(i, 0, 60) if (F[60] + F[i] <= m) if (F[i] > F[p]) p = i;
      ans.emplace_back(60 - p);
      f(F, 60 - p);
    }
    if (sz(ans) <= 60) {
      debug(F[60]);
      cout << sz(ans) << "\n";
      for (int x : ans) {
        cout << x << " ";
      }
      cout << "\n";
      break;
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}