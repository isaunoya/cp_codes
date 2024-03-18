#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (int i = 0; i < a; i++)
#define rep2(i, a) for (int i = 0; i < a; i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
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

const int N = 3005;
double dp[N][N];
void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dp[i][j] = inf;
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    auto solve = [&](auto self, int l, int r, int L, int R) -> void {
      if (l > r) {
        return;
      }
      int m = (l + r) / 2, p = L;
      rep(x, L, min(R + 1, m)) {
        if (dp[i - 1][x] + 1. * x / (m - x) < dp[i - 1][p] + 1. * p / (m - p)) {
          p = x;
        }
      }
      dp[i][m] = dp[i - 1][p] + 1. * p / (m - p);
      self(self, l, m - 1, L, p);
      self(self, m + 1, r, p, R);
    };
    solve(solve, i, m, i - 1, m);
  }
  cout << fixed << setprecision(12) << dp[n][m] * 2 + n - 2 << "\n";

}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}