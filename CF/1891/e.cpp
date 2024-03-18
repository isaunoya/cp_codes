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

int n, k;
const int N = 1e5 + 500;
int a[N];
int coef[N][2][2];
int dp[2][N][2];
int vis[2][N][2];
int sum[N];

void solve() {
  cin >> n >> k;
  rep(i, n) {
    cin >> a[i];
  }
  rep(i, 1, n) {
    rep(j, 2) {
      rep(nj, 2) {
        int x = a[i - 1];
        int y = a[i];
        if (j == 1) {
          x = 0;
        }
        if (nj == 1) {
          y = 0;
        }
        if (gcd(x, y) == 1) {
          coef[i][j][nj] = 1;
        } else {
          coef[i][j][nj] = 0;
        }
      }
    }
  }

  rep(c, 0, 2) rep(i, k + 1) rep(j, 2) dp[c][i][j] = inf, vis[c][i][j] = -1;
  dp[0][0][0] = 0;
  dp[0][1][1] = 0;
  vis[0][0][0] = 0;
  vis[0][1][1] = 0;
  int p = 1, q = 0;
  for (int i = 1; i < n; i++, p ^= 1, q ^= 1) {
    int l = 1ll * k * (i + 1) / n - 500;
    int r = 1ll * k * (i + 1) / n + 500;
    cmax(l, 0);
    cmin(r, k);
    rep(kk, l, r + 1) {
      dp[p][kk][0] = dp[p][kk][1] = inf;
      rep(j, 2) {
        rep(nj, 2) {
          if (kk >= nj) {
            if (vis[q][kk - nj][j] < i - 1) continue;
            cmin(dp[p][kk][nj], dp[q][kk - nj][j] + coef[i][j][nj]);
            vis[p][kk][nj] = i;
          }
        }
      }
    }
  }

  cout << min(dp[q][k][0], dp[q][k][1]) << "\n";
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