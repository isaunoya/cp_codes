#include <queue>
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
  ll n, l;
  cin >> n >> l;
  vl a(n), b(n);
  rep(i, n) cin >> a[i] >> b[i];
  vi p(n); iota(all(p), 0);
  sort(all(p), [&](int i, int j) {
    return b[i] < b[j];
  });
  int ans = 0;
  for (int i = 0; i < n; i++) {
    priority_queue<ll> q;
    ll cur = 0;
    for (int j = i; j < n; j++) {
      cur += a[p[j]];
      q.emplace(a[p[j]]);
      while (!q.empty() && cur + b[p[j]] - b[p[i]] > l) {
        auto x = q.top();
        cur -= x;
        q.pop();
      }
      cmax(ans, (int)q.size());
      // debug(i, j, q.size());
    }
  }
  cout << ans << "\n";
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