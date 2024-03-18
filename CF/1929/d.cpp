#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
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
const int P = 998244353;

void solve() {
  int n;
  cin >> n;
  vc<vi> g(n);
  vc<array<ll, 3>> dp(n);
  rep(i, n) { rep(a, 3) dp[i][a] = -1; }
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    g[a].pb(b);
    g[b].pb(a);
  }
  auto dfs = [&](auto &dfs, int u, int state, int p) -> ll {
    if (!state) {
      return 1LL;
    }
    if (~dp[u][state]) {
      return dp[u][state];
    }
    ll &res = dp[u][state] = (state == 1);
    for (auto v : g[u]) {
      if (v != p) {
        if (state == 1) {
          res *= dfs(dfs, v, state, u) + 1;
          res %= P;
        } else {
          res += dfs(dfs, v, 1, u) + dfs(dfs, v, 2, u);
        }
      }
    }
    res %= P;
    return res;
  };
  ll ans = 0;
  rep(a, 3) ans += dfs(dfs, 0, a, -1);
  cout << ans % P << "\n";
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