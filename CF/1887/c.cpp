#include <bits/stdc++.h>
#include <cmath>
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

const int N = 5e5 + 5;
int s[N * 4], tag[N * 4];
void build(int l, int r, int p) {
  tag[p] = -1;
  s[p] = r - l + 1;
  if (l == r) {
    return;
  }
  int m = (l + r) / 2;
  build(l, m, p * 2);
  build(m + 1, r, p * 2 + 1);
}

void pu(int x) { s[x] = s[x * 2] + s[x * 2 + 1]; }

void psd(int x) {
  tag[x] = 0;
  s[x] = 0;
}
void push(int x) {
  if (tag[x])
    return;
  psd(x * 2);
  psd(x * 2 + 1);
  tag[x] = -1;
}

void upd(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    psd(p);
    return;
  }
  push(p);
  int m = (l + r) / 2;
  if (ql <= m) {
    upd(ql, qr, l, m, p * 2);
  }
  if (qr > m) {
    upd(ql, qr, m + 1, r, p * 2 + 1);
  }
  pu(p);
}

int query(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    return s[p];
  }
  push(p);
  int m = (l + r) / 2;
  int res = 0;
  if (ql <= m) {
    res += query(ql, qr, l, m, p * 2);
  }
  if (qr > m) {
    res += query(ql, qr, m + 1, r, p * 2 + 1);
  }
  return res;
}

void solve() {
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];
  int q;
  cin >> q;
  vc<vc<pair<ll, ll>>> b(n);
  vc<array<ll, 3>> querys;
  querys.pb(array<ll, 3>{0, 0, 0});
  rep(i, n) { b[i].pb(0, 0); }
  rep(i, 1, q + 1) {
    int l, r, x;
    cin >> l >> r >> x;
    --l;
    b[l].pb(i, x);
    if (r < n)
      b[r].pb(i, -x);
    querys.pb(array<ll, 3>{x, l, r});
  }
  for (auto &v : b) {
    v.pb(q + 1, 0);
    ll lst = 0;
    for (auto &[i, vv] : v) {
      vv += lst;
      lst = vv;
    }
  }
  build(0, q, 1);
  for (auto &v : b) {
    vc<array<ll, 3>> seg;
    for (int i = 0; i + 1 < sz(v); i++) {
      ll l = v[i].fi;
      ll r = v[i + 1].fi - 1;
      ll val = v[i].se;
      seg.pb(array<ll, 3>{val, l, r});
    }
    sort(all(seg));
    ll p = -lnf;
    for (auto [val, l, r] : seg) {
      if (query(l, r, 0, q, 1)) {
        p = val;
        break;
      }
    }
    assert(p != -lnf);
    for (auto [val, l, r] : seg) {
      if (val == p) {
        continue;
      }
      upd(l, r, 0, q, 1);
    }
  }

  int p = 0;
  for (int i = 0; i <= q; i++) {
    if (query(i, i, 0, q, 1)) {
      p = i;
      break;
    }
  }
  vc<ll> c(n + 1);
  for (int i = 0; i <= p; i++) {
    auto [v, l, r] = querys[i];
    c[l] += v;
    c[r] -= v;
  }
  rep(i, 1, n + 1) { c[i] += c[i - 1]; }
  rep(i, n) { cout << a[i] + c[i] << " "; }
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