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

void solve() {
  int n, m, x;
  cin >> n >> m >> x;
  x--;
  vector<bool> dp(n, false);
  dp[x] = true;
  for (int i = 0; i < m; i++) {
    int c;
    char op;
    cin >> c >> op;
    vector<bool> ndp(n, false);
    if (op == '1' || op == '?') {
      for (int j = 0; j < n; j++) {
        int k = (j + n - c) % n;
        if (dp[j]) {
          ndp[k] = true;
        }
      }
    }
    if (op == '0' || op == '?') {
      for (int j = 0; j < n; j++) {
        int k = (j + c) % n;
        if (dp[j]) {
          ndp[k] = true;
        }
      }
    }
    dp.swap(ndp);
  }
  vi ans;
  rep(i, n) if (dp[i]) ans.pb(i);
  cout << sz(ans) << "\n";
  for (int x : ans) {
    cout << x + 1 << " ";
  }
  cout << "\n";
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