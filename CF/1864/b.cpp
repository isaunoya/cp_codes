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
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  if (k % 2 == 0) {
    sort(all(s));
    cout << s << "\n";
  } else {
    vector<char> s1, s2;
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
        s1.emplace_back(s[i]);
      } else {
        s2.emplace_back(s[i]);
      }
    }
    sort(all(s1));
    sort(all(s2));
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
        cout << s1[i / 2];
      } else {
        cout << s2[i / 2];
      }
    }
    cout << "\n";
  }
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
