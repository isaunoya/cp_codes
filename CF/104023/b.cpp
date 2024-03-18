#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (int i = 0; i < a; i++)
#define rep2(i, a) for (int i = 0; i < a; i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
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

void solve() {
  int n;
  cin >> n;
  vc<ll> a(n);
  rep(i, n) cin >> a[i];
  ll t = a.back();
  vc<ll> d;
  rep(i, 1, sqrt(t) + 1) {
    if (t % i == 0) {
      d.pb(i);
      d.pb(t / i);
    }
  }
  sort(all(d));
  d.resize(unique(all(d)) - begin(d));
  vc<array<ll, 3>> w;
  for (auto x : d) {
    for (auto y : d) {
      ll dd = x * y - x - y;
      w.pb(array<ll, 3>{dd, x, y});
    }
  }
  sort(all(w));
  vc<pii> comp;
  comp.pb(t, 0);
  vc<pii> ops;
  for (int i = n - 2; i >= 0; i--) {
    int dd = a[i + 1] - a[i];
    int l = lower_bound(all(w), array<ll, 3>{dd, 0, 0}) - begin(w);
    int r = lower_bound(all(w), array<ll, 3>{dd + 1, 0, 0}) - begin(w);
    map<ll, bool> mp;
    for (auto [x, y] : comp)
      mp[x] = 1;
    mp[1] = 1;
    vc<array<ll, 2>> tmp;
    ll p = -inf, x0, y0;
    rep(j, l, r) {
      auto [dd, x, y] = w[j];
      if (mp[x * y]) {
        p = x * y, x0 = x, y0 = y;
        break;
      }
    }
    if (p == -inf) {
      cout << "-1\n";
      return;
    }
    if (min(x0, y0) == 1) {
      ops.pb(comp[0].first, 1);
      comp[0].second += 1;
      continue;
    }
    ops.pb(x0, y0);
    vc<pii> comp2;
    for (auto [x, y] : comp) {
      if (x == p) {
        comp2.pb(x0, 0);
        comp2.pb(y0, y);
        p = -inf;
      } else {
        comp2.pb(x, y);
      }
    }
    comp.swap(comp2);
  }
  vi ans;
  for (auto [x, y] : comp) {
    ans.pb(x);
    while (y--)
      ans.pb(1);
  }
  for (auto i : ans)
    cout << i << " ";
  cout << "\n";
  vc<array<int, 3>> cp;
  int sz = 0;
  for (auto [x, y] : comp) {
    cp.pb(array<int, 3>{x, y, sz});
    sz += y + 1;
  }
  reverse(all(ops));
  vi xs;
  for (auto [x, y] : ops) {
    debug(x, y, cp);
    if (y == 1) {
      for (int i = 0; i < sz(cp); i++) {
        if (cp[i][0] == x) {
          xs.pb(cp[i][2]);
          cp[i][2] += 1;
          break;
        }
      }
    } else {
      vc<array<int, 3>> ncp;
      for (int i = 0; i < sz(cp); i++) {
        auto [xx, yy, zz] = cp[i];
        if (i + 1 < cp.size() && xx == x && cp[i + 1][0] == y) {
          xs.pb(zz);
          ncp.pb(array<int, 3>{x * y, yy, zz + 1});
          i += 1;
        } else {
          ncp.pb(array<int, 3>{xx, yy, zz});
        }
      }
      cp.swap(ncp);
    }
  }
  for (int x : xs) {
    cout << x + 1 << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}