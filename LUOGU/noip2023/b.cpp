#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

#define int long long
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
#define all(x) begin(x), end(x)
#define fi first
#define se second

const int N = 4e5 + 5;
ll f[N * 4], g[N * 4];
void up(int p) { f[p] = max(f[p * 2], f[p * 2 + 1]); }
void build(int l, int r, int p) {
  f[p] = g[p] = 0;
  if (l == r)
    return;
  int m = (l + r) / 2;
  build(l, m, p * 2), build(m + 1, r, p * 2 + 1);
}

void ps(int p, ll v) { f[p] += v, g[p] += v; }

void down(int p) {
  if (g[p] == 0)
    return;
  ps(p * 2, g[p]), ps(p * 2 + 1, g[p]);
  g[p] = 0;
}

void add(int ql, int qr, int l, int r, int p, ll v) {
  if (ql <= l && r <= qr) {
    ps(p, v);
    return;
  }
  down(p);

  int m = (l + r) / 2;
  if (ql <= m)
    add(ql, qr, l, m, p * 2, v);
  if (qr > m)
    add(ql, qr, m + 1, r, p * 2 + 1, v);
  up(p);
}
ll query(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr)
    return f[p];
  down(p);
  int m = (l + r) / 2;
  ll res = 0;
  if (ql <= m)
    cmax(res, query(ql, qr, l, m, p * 2));
  if (qr > m)
    cmax(res, query(ql, qr, m + 1, r, p * 2 + 1));
  return res;
}

void solve() {
  int n, m, k, D;
  cin >> n >> m >> k >> D;
  vi s;
  vc<tuple<int, int, int>> o;
  rep(i, m) {
    int x, y, v;
    cin >> x >> y >> v;
    int l = x - y + 1;
    int r = x;
    s.pb(l - 1), s.pb(r + 1);
    o.pb(l, r, v);
  }
  sort(all(s));
  s.resize(unique(all(s)) - s.begin());
  int sz = s.size();
  build(0, sz, 1);

  vc<vc<pii>> t(sz);
  rep(i, m) {
    auto [l, r, v] = o[i];
    int c = lower_bound(all(s), l - 1) - s.begin();
    int d = lower_bound(all(s), r + 1) - s.begin();
    t[d].pb(c, v);
  }
  int l = 0;
  ll ans = 0;
  add(0, 0, 0, sz, 1, 1ll * s[0] * D);
  rep(i, 1, sz) {
    for (auto [j, v] : t[i]) {
      add(0, j, 0, sz, 1, v);
    }
    while ((s[i] - 1) - (s[l] + 1) + 1 > k)
      l++;
    cmax(ans, query(l, i - 1, 0, sz, 1) - 1ll * (s[i] - 1) * D);
    // cout << dp[i] << "\n";
    add(i, i, 0, sz, 1, ans + 1ll * s[i] * D);
  }
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1, c;
  cin >> c >> t;
  while (t--) {
    solve();
  }
  return 0;
}