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

const int B = 1000;
const int N = 4e5 + 5;
ll a[N], b[N], dp[B][B];
ll dp2[2][N];
ll vis[2][N];

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  rep(i, n) cin >> a[i];
  rep(i, n) cin >> b[i];
  if (n < B) {
    int cnt1 = count(all(s), '1');
    rep(i, n + 1) {
      rep(j, cnt1 + 1) { dp[i][j] = -lnf; }
    }
    dp[0][0] = 0;
    rep(i, n) {
      int x = s[i] - '0';
      rep(j, cnt1) {
        // choose red
        if (x == 1)
          cmax(dp[i + 1][j + 1], dp[i][j] + a[i]);
        else
          cmax(dp[i + 1][j], dp[i][j] + a[i] - j);
        // choose blue
        cmax(dp[i + 1][j], dp[i][j] + b[i]);
      }
    }
    cout << *max_element(dp[n], dp[n] + cnt1 + 1) << "\n";
  } else {
    ll ans = 0;
    rep(i, n) ans += b[i];
    ll res = 0, pre1 = 0;
    rep(i, n) {
      int x = s[i] - '0';
      if (a[i] > b[i]) {
        res += a[i];
        if (x == 1) {
          pre1++;
        } else {
          res -= pre1;
        }
      } else {
        res += b[i];
      }
    }
    cmax(ans, res);
    ll c1 = 0;
    rep(i, 2) rep(j, n + 1) { dp2[i][j] = -lnf, vis[i][j] = -1; }
    dp2[0][0] = 0;
    vis[0][0] = 0;
    int p = 1, q = 0;
    rep(i, n) {
      int x = s[i] - '0';
      if (x == 1) {
        c1++;
      }

      int l = c1 - 2 * B;
      int r = c1;
      cmax(l, 0);
      rep(j, l, r + 1) {
        // choose red
        if (x == 1) {
          if (vis[q][j] == i) {
            cmax(dp2[p][j + 1], dp2[q][j] + a[i]);
            vis[p][j + 1] = i + 1;
          }
        } else {
          if (vis[q][j] == i) {
            cmax(dp2[p][j], dp2[q][j] + a[i] - j);
            vis[p][j] = i + 1;
          }
        }
        // choose blue
        if (vis[q][j] == i) {
          cmax(dp2[p][j], dp2[q][j] + b[i]);
          vis[p][j] = i + 1;
        }
      }
      l = 0;
      r = 2 * B;
      rep(j, l, r + 1) {
        // choose red
        if (x == 1) {
          if (vis[q][j] == i) {
            cmax(dp2[p][j + 1], dp2[q][j] + a[i]);
            vis[p][j + 1] = i + 1;
          }
        } else {
          if (vis[q][j] == i) {
            cmax(dp2[p][j], dp2[q][j] + a[i] - j);
            vis[p][j] = i + 1;
          }
        }
        // choose blue
        if (vis[q][j] == i) {
          cmax(dp2[p][j], dp2[q][j] + b[i]);
          vis[p][j] = i + 1;
        }
      }
      p ^= 1, q ^= 1;
    }
    rep(i, n + 1) if (vis[q][i] == n) { cmax(ans, dp2[q][i]); }
    cout << ans << "\n";
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