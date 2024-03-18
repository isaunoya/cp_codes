#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define eb emplace_back
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
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i, 0, n) cin >> a[i];
  sort(all(a));
  vector<int> b;
  vector<int> c;
  for (auto x : a) {
    if (x == a[0]) {
      b.emplace_back(x);
    } else {
      c.emplace_back(x);
    }
  }
  if (c.empty()) {
    cout << -1 << "\n";
    return;
  }
  cout << b.size() << " " << c.size() << "\n";
  for (int x : b)
    cout << x << " ";
  cout << "\n";
  for (int x : c)
    cout << x << " ";
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