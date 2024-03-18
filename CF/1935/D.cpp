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
  ll n, C;
  cin >> n >> C;

  vi s(n);
  rep(i, n) {
    cin >> s[i];
  }

  ll ans = 1ll * (C + 1) * (C + 2) / 2;
  // all pairs

  // if s[i] = y+x, then it will delete all pairs of (<s[i], s[i])
  // if s[i] = y-x, then it will delete all pairs of (s[i], >s[i])
  // debug(ans);

  array<int, 2> cnt;
  auto get = [&](int val, int c) { // <val, %2=c
    int odd = val / 2;
    int even = val - odd;
    return (c == 0 ? even : odd);
  };
  rep(i, n) {
    ans -= 1ll * get(s[i], s[i] % 2);
  }
  auto get2 = [&](int val, int c) { // val<cur<=2*c-val, %2=c
    return get(2 * C - val + 1, val % 2) - get(val, val % 2);
  };
  for (int i = n - 1; i >= 0; i--) {
    ans -= 1ll * get2(s[i], s[i] % 2);
  }
  // debug(ans);
  rep(i, 2) cnt[i] = 0;
  rep(i, n) cnt[s[i] % 2] += 1;
  ans -= cnt[0] + cnt[1];
  ans += 1ll * cnt[0] * (cnt[0] + 1) / 2;
  ans += 1ll * cnt[1] * (cnt[1] + 1) / 2;
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