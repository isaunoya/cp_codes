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
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<ll, ll>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second
#endif

ll get(ll x, ll y) { return (x + y) * (y - x + 1) / 2; }

void solve() {
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];
  vl s(n + 1);
  rep(i, n) s[i + 1] = s[i] + a[i];
  int q;
  cin >> q;
  while (q--) {
    int l, u;
    cin >> l >> u;
    --l;
    int L = l, R = n + 1;
    while (R - L > 1) {
      int M = (L + R) / 2;
      if (u - s[M] + s[l] + 1 > 0) {
        L = M;
      } else {
        R = M;
      }
    }

    int r = l + 1;
    rep(i, max(L, l + 1), min(L + 100, n + 1)) {
      if (get(u - s[i] + s[l] + 1, u) > get(u - s[r] + s[l] + 1, u)) {
        r = i;
      }
    }
    cout << r << " \n"[q == 0];
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