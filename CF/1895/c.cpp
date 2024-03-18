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

int coef[10][50];
void solve() {
  int n;
  cin >> n;
  vc<string> s(n);
  rep(i, n) cin >> s[i];
  ll ans = 0;
  for (int l = 2; l <= 10; l += 2) {
    memset(coef, 0, sizeof coef);
    rep(i, n) {
      if (sz(s[i]) < l) {
        int sum = 0;
        int c = 0;
        for (int j = sz(s[i]) - 1; j >= 0; j--) {
          c += 1;
          if (c > l / 2) {
            sum -= s[i][j] - '0';
          } else {
            sum += s[i][j] - '0';
          }
        }
        if (sum >= 0) coef[sz(s[i])][sum] += 1;
        sum = 0;
        c = 0;
        rep(j, sz(s[i])) {
          c += 1;
          if (c > l / 2) {
            sum -= s[i][j] - '0';
          } else {
            sum += s[i][j] - '0';
          }
        }
        if (sum >= 0) coef[sz(s[i])][sum] += 1;
      }
    }
    rep(i, 1, l) {
      rep(j, 50) {
        ans += 1ll * coef[i][j] * coef[l - i][j];
      }
    }
  }

  cout << ans / 4 << "\n";
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