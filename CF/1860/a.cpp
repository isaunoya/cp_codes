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
  string s;
  cin >> s;
  int n = sz(s);
  string s0;
  rep(i, 0, n) { s0 += "()"; }
  if (s0.find(s) == s0.npos) {
    cout << "YES\n";
    cout << s0 << "\n";
    return;
  }
  string s1;
  rep(i, 0, n) { s1 += "("; }
  rep(i, 0, n) { s1 += ")"; }
  if (s1.find(s) == s1.npos) {
    cout << "YES\n";
    cout << s1 << "\n";
    return;
  }
  cout << "NO\n";
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
