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
ll C[40][40];
ll dp[51][220][20];
void md(ll &x) {
  if (x >= P)
    x -= P;
}
void solve() {
  ll N, M, K;
  cin >> N >> M >> K;
  dp[50][0][K] = 1;
  for (int i = 49; i >= 0; i--) {
    ll lim = M >> i;
    rep(a, 200) { // exceed from higher bit
      ll s = (N >> i) - a;
      rep(b, K + 1) {
        rep(c, b + 1) {
          rep(d, K - b + 1) {
            ll x1 = c + d, x0 = K - x1;
            ll x = x1 * x0;
            if (lim == 0 && c > 0)
              continue;
            if (lim <= 1 && d > 0)
              continue;
            if (x > s)
              continue;
            if (s - x & 1)
              continue;
            ll a1 = (N >> i + 1) - (s - x) / 2;
            ll b1 = lim % 2 == 0 ? b - c : K - d;
            md(dp[i][a][b] +=
               dp[i + 1][a1][b1] * C[b][c] % P * C[K - b][d] % P);
          }
        }
      }
    }
  }
  cout << dp[0][0][K] << "\n";
}

int main() {
  rep(i, 40) {
    C[i][0] = C[i][i] = 1;
    rep(j, 1, i) { md(C[i][j] = C[i - 1][j - 1] + C[i - 1][j]); }
  }
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}