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
  int n, b, k1, k2;
  cin >> n >> b >> k1 >> k2;
  ll sum = 0;
  vector<int> a(n);
  rep(i, 0, n) cin >> a[i], sum += a[i];
  auto func = [&](bool u, bool v, int x) {
    int ori = x;
    if (u)
      x = (x + 1) / 2;
    if (v)
      x = max(x - b, 0);
    return ori - x;
  };
  vector<ll> q(4), nq(4);
  vector<array<int, 4>> v(n);
  auto solve = [&](int m) {
    if (m < 0)
      return -1ll;
    ll ans = lnf;
    array<int, 4> c{n + m - k1 - k2, k1 - m, k2 - m, m};
    rep(i, 0, n) rep(j, 0, 4) v[i][j] = func(j & 1, j >> 1, a[i]);
    q = {0, 0, 0, 0};
    auto calc = [&](const auto &q) {
      ll res = 0;
      rep(i, 0, n) res +=
          max({v[i][0] - q[0], v[i][1] - q[1], v[i][2] - q[2], v[i][3] - q[3]});
      rep(i, 0, 4) res += (ll)c[i] * q[i];
      return res;
    };
    for (ll w = 1LL << 31; w; w >>= 1) {
      rep(t, 0, 4) {
        rep(s, 0, 1 << 4) {
          nq = q;
          rep(i, 0, 4) if (s >> i & 1) nq[i] += w;
          ll res = calc(nq);
          if (res < ans)
            ans = res, q = nq;
        }
      }
      if (ans < 0)
        return ans;
    }
    return ans;
  };
  int L = max(k1 + k2 - n, 0) - 1, R = min(k1, k2) + 1;
  ll ans = 0;
  while (R - L > 2) {
    int ml = (L + R) / 2;
    int mr = ml + 1;
    ll ansl = solve(ml), ansr = solve(mr);
    if (ansl > ansr) {
      R = mr;
      cmax(ans, ansl);
    } else {
      L = ml;
      cmax(ans, ansr);
    }
  }
  rep(i, L, R) cmax(ans, solve(i));
  cout << sum - ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  cin >> tt;
  while (tt--) {
    run_case();
  }

  return 0;
}
