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
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < n; j++) {
      if (s[j] == '1') {
        a[i][j] = 1;
      }
    }
  }
  unordered_map<int, int> mp1, mp2;
  vector<int> b(n);
  int row = 0, ans = 0;
  while (row < n) {
    rep(j, 0, n) b[j] = 0;
    for (auto [x, c] : mp1) {
      b[max(0, x - row)] ^= c;
    }
    for (auto [x, c] : mp2) {
      if (x + row < n)
        b[x + row] ^= c;
    }
    for (int j = 0; j < n; j++) {
      if (j) {
        b[j] ^= b[j - 1];
      }
      a[row][j] ^= b[j];
    }
    for (int j = 0; j < n; j++) {
      if (a[row][j] == 1) {
        ans += 1;
        int y0 = j + row;
        int y1 = j - row;
        mp1[y0] ^= 1;
        mp2[y1 + 1] ^= 1;
      }
    }
    row++;
  }
  cout << ans << "\n";
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
