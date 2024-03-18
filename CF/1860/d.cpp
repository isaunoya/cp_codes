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

const int N = 105;
const int M = N * (N - 1);
struct myarray {
  int a[M];
  void clear() { memset(a, 0x3f, sizeof a); }
  int &operator[](int x) { return a[M / 2 + x]; }
} f[2][N];
// i, cnt, delta
// delta = 10 - 01
void solve() {
  string s;
  cin >> s;
  int p = 0;
  int n = sz(s);
  f[0][0][0] = 0;
  for (int i = 0; i < n; i++) {
    p ^= 1;
    for (int k = 0; k <= i + 1; k++)
      f[p][k].clear();
    int len = i + 1;
    int mx_delta = len * (len - 1) / 2;
    for (int j = -mx_delta; j <= mx_delta; j++) {
      for (int k = 0; k < len; k++) {
        int cnt1 = k;
        int cnt0 = len - 1 - k;
        if (s[i] == '0') {
          cmin(f[p][k][j + cnt1], f[p ^ 1][k][j]);         // 10
          cmin(f[p][k + 1][j - cnt0], f[p ^ 1][k][j] + 1); // 01
        } else {
          cmin(f[p][k + 1][j - cnt0], f[p ^ 1][k][j]); // 01
          cmin(f[p][k][j + cnt1], f[p ^ 1][k][j] + 1); // 10
        }
      }
    }
  }
  int c1 = 0;
  rep(i, 0, n) if (s[i] == '1') c1++;
  cout << f[p][c1][0] / 2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}
