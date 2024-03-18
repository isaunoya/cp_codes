#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
using namespace std;
#define tr(x, v) for (auto &x : v)
#define rp(i, v) for (int i = 0; i < sz(v); i++)
#define rep(i, x, y) for (int i = x; i < y; i++)
#define pr(i, v) for (int i = sz(v) - 1; i >= 0; i--)
#define per(i, x, y) for (int i = x; i > y; i--)
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  if (x > y)
    x = y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  if (x < y)
    x = y;
}
using ll = long long;
using E = vector<vector<int>>;
using EW = vector<vector<array<int, 2>>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define ed(x) end(x)
#define all(x) bg(x), ed(x)
#define lb lower_bound
#define ub upper_bound
#define unique(x) (x).erase(unique(all(x)), x.end())
void out(bool t) { cout << (t ? "YES" : "NO") << "\n"; }
template <class T> T max(const vector<T> &v) { return *max_element(all(v)); }
template <class T> T min(const vector<T> &v) { return *min_element(all(v)); }
template <class T> istream &operator>>(istream &is, vector<T> &v) {
  tr(x, v) { is >> x; }
  return is;
}
template <class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  if (v.empty()) {
    os << "\n";
  } else {
    rp(i, v) os << v[i] << " \n"[i + 1 == (int)v.size()];
  }
  return os;
}

void run_case() {
  int n, k;
  cin >> n >> k;
  int a[n + 1], cold[k + 1], hot[k + 1];
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= k; i++) cin >> cold[i];
  for (int i = 1; i <= k; i++) cin >> hot[i];
  a[0] = cold[0] = hot[0] = 0;
/*
  ll dp[n + 1][k + 1];
  for (int i = 0; i <= n; i++) for (int j = 0; j <= k; j++) dp[i][j] = lnf;
  dp[1][0] = cold[a[1]];
  for (int i = 2; i <= n; i++) {
    int lst = a[i - 1];
    for (int j = 0; j <= k; j++) {
      cmin(dp[i][j], dp[i - 1][j] + (a[i] == lst ? hot[a[i]] : cold[a[i]]));
      cmin(dp[i][lst], dp[i - 1][j] + (a[i] == j ? hot[a[i]] : cold[a[i]]));
    }
  }
*/
  /*
  ll ans = lnf;
  rep (j, 0, k + 1) cmin(ans, dp[n][j]);
  */
  ll sum = 0;
  rep (i, 1, n + 1) sum += (a[i] == a[i - 1]) ? hot[a[i]] : cold[a[i]];
  ll dp[k + 1];
  rep (i, 1, k + 1) dp[i] = lnf;
  dp[0] = 0;
  ll mn = lnf;
  cmin(mn, dp[0]);
  for (int i = 1; i <= n; i++) {
    if (a[i] != a[i - 1]) {
      int lst = a[i - 1];
      // a[i] == j, dp[j]+hot
      // a[i] != j, mn+cold
      dp[lst] = min(dp[a[i]] + hot[a[i]] - cold[a[i]], mn);
      cmin(mn, dp[lst]);
    }
  }
  cout << sum + mn << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    run_case();
  }

  return 0;
}
