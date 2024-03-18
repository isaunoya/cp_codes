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

#define int long long
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n + 1), b(m + 1), c(k + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
  }
  for (int i = 1; i <= k; ++i) {
    cin >> c[i];
  }
  sort(a.begin() + 1, a.end());
  sort(b.begin() + 1, b.end());
  sort(c.begin() + 1, c.end());
  int p1 = 0, v1 = 0, p2 = 0, v2 = 0;
  for (int i = 1; i < n; ++i) {
    int x = a[i + 1] - a[i];
    if (x > v1)
      v2 = v1, p2 = p1, v1 = x, p1 = i; // 找到最大和次大的值和位置
    else {
      if (x > v2)
        v2 = x, p2 = i;
    }
  }
  int op = (a[p1 + 1] + a[p1]) / 2; // 最大值中间位置
  int ans = v1;
  for (int i = 1; i <= m; ++i) {
    int y = op - b[i];
    int t = lower_bound(c.begin() + 1, c.end(), y) - c.begin();
    int ret1 = LNF, ret2 = LNF;
    // 中间位置前驱后继的答案
    if (t <= k && a[p1 + 1] >= c[t] + b[i] && c[t] + b[i] >= a[p1]) {
      ret1 = max(a[p1 + 1] - (c[t] + b[i]), (c[t] + b[i]) - a[p1]);
    }
    if (t > 1) {
      --t;
      if (a[p1 + 1] >= c[t] + b[i] && c[t] + b[i] >= a[p1]) {
        ret2 = max(a[p1 + 1] - (c[t] + b[i]), (c[t] + b[i]) - a[p1]);
      }
    }
    ans = min(ans, max(v2, min(ret1, ret2)));
  }
  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}