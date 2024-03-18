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

int dp[5005][25];
int f(int n, int k) {
  if (dp[n][k] != -1) {
    return dp[n][k];
  }
  if (n == 0) {
    return 0;
  }
  if (k == 1) {
    return n;
  }
  int m = inf;
  for (int i = 1; i <= n; i++) {
    cmin(m, max(f(i - 1, k - 1), f(n - i, k)));
  }
  return dp[n][k] = m + 1;
}
void solve() {
  int N, K;
  cin >> N >> K;
  if (K == 1) {
    cout << N << " " << 1 << "\n";
    return;
  }
  int fir = -1;
  int lst = -1;
  int ans = f(N, K);
  cout << ans << " ";
  for (int i = 1; i <= N; i++) {
    if (ans == max(f(i - 1, K - 1), f(N - i, K)) + 1) {
      if (fir == -1) {
        fir = i;
      }
      lst = i;
    }
  }
  if (fir < lst)
    cout << fir << "-" << lst << "\n";
  else
    cout << fir << "\n";
}

int main() {
  memset(dp, -1, sizeof dp);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}