#if defined(LOCAL)
#include <D:/cp/templates/my_template_compiled.hpp>
#else
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#define debug(...) 42
#define rep1(a) for (auto i = 0; i < a; i++)
#define rep2(i, a) for (auto i = 0; i < a; i++)
#define rep3(i, a, b) for (auto i = a; i < b; i++)
#define rep4(i, a, b, c) for (auto i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define pb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  x = x < y ? x : y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  x = x > y ? x : y;
}
template <typename T> using vc = vector<T>;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second
#endif

const int N = 1e6 + 2;
int dp[N][3][3];

string t1 = "map";
string t2 = "pie";

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  for (int i = 0; i <= n; i++) {
    rep(j, 3) rep(k, 3) dp[i][j][k] = INF;
  }
  dp[0][0][0] = 0;
  rep(i, n) {
    rep(j, 3) rep(k, 3) {
      int nj = (s[i] == t1[j]) ? (j + 1) : (s[i] == t1[0]);
      int nk = (s[i] == t2[k]) ? (k + 1) : (s[i] == t2[0]);
      cmin(dp[i + 1][j][k], dp[i][j][k] + 1);
      if (nj == 3 || nk == 3) continue;
      cmin(dp[i + 1][nj][nk], dp[i][j][k]);
    }
  }
  int ans = INF;
  rep(j, 3) rep(k, 3) cmin(ans, dp[n][j][k]);

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