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

const int U = (1 << 30) - 1;
void solve() {
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];
  vi pre(n + 1), suf(n + 1);
  auto solve = [&]() {
    pre[0] = U;
    rep(i, n) pre[i + 1] = pre[i] & a[i];
    suf[n] = U;
    for (int i = n - 1; i >= 0; i--)
      suf[i] = suf[i + 1] & a[i];
    ll ans = 0;
    rep(i, 1, n) cmax(ans, pre[i] + suf[i]);
    return ans;
  };
  ll ans = solve();
  rep(i, n) cmax(ans, a[i] + (pre[i] & suf[i + 1]));

  auto get_ans = [&](int x, int y) {
    swap(a[x], a[y]);
    ll res = solve();
    swap(a[x], a[y]);
    return res;
  };

  vi p;
  int x = U;
  rep(i, n) if ((x & a[i]) < x) {
    p.pb(i);
    x &= a[i];
  }

  x = U;
  for (int i = n - 1; i >= 0; i--)
    if ((x & a[i]) < x) {
      p.pb(i);
      x &= a[i];
    }

  sort(all(p));
  p.resize(unique(all(p)) - p.begin());
  rep(i, p.size()) {
    rep(j, i + 1, p.size()) { cmax(ans, get_ans(p[i], p[j])); }
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