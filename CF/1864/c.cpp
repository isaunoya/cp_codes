#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
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
#define all(x) begin(x), end(x)

void solve() {
  int x;
  cin >> x;
  vector<int> ans{1};
  while (ans.back() * 2 <= x) {
    ans.emplace_back(ans.back() * 2);
  }
  x -= ans.back();
  for (int i = 30; i >= 0; i--) {
    if (x >> i & 1) {
      ans.emplace_back(ans.back() + (1LL << i));
    }
  }
  reverse(all(ans));
  cout << sz(ans) << "\n";
  for (int x : ans) {
    cout << x << " ";
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
