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

const int P = 1e9 + 7;
const int iv2 = (P + 1) / 2;

void md(int &x) {
  if (x >= P) {
    x -= P;
  }
}

void solve() {
  int N, M;
  cin >> N >> M;
  int ans = 0;
  vi a(N);
  rep(i, N) cin >> a[i], --a[i], ans += M - a[i];
  vc<vi> dp(M, vi(M));
  rep(i, N - 1) dp[a[i]][a[i + 1]] = 1;
  rep(i, M) {
    rep(j, i + 1, M) {
      int x = dp[i][j];
      x = 1ll * x * iv2 % P;
      if (j + 1 < M)
        md(dp[i][j + 1] += x);
      if (i + 1 < M)
        md(dp[i + 1][j] += x);
    }
  }
  rep(i, M) md(ans += P - 1ll * dp[i][i] * (M - i) % P);
  cout << ans << "\n";
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