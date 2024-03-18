#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
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
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

const int M = 2505;
int dp[M][M];
const int P = 998244353;

void solve() {
  int N, K;
  cin >> N >> K;
  rep(i, N + 1) rep(j, K + 1) dp[i][j] = 0;
  rep(i, K) dp[0][i] = 1;
  rep(i, 1, N + 1) {
    rep(x, i + 1) {
      for (int y = 0;; y++) {
        int cnt = (x + 1) * (y + 1);
        int len = x + 1 + y;
        if (cnt > i)
          break;
        if (len > K)
          break;
        dp[i][y] += dp[i - cnt][x];
        if (dp[i][y] >= P) {
          dp[i][y] -= P;
        }
      }
    }
  }
  int ans = 0;
  rep(i, K) {
    ans += dp[N][i];
    if (ans >= P) {
      ans -= P;
    }
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