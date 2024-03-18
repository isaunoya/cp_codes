#include <algorithm>
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

const int N = 2e6 + 5;

ll tag[N * 4], s[N * 4], len[N * 4], f[N * 4];

void up(int p) {
  f[p] = max(f[p * 2], f[p * 2 + 1]);
  s[p] = s[p * 2] + s[p * 2 + 1];
}

void push(int p, int v) {
  s[p] = len[p] * v;
  tag[p] = v;
  f[p] = v;
  return;
}
void down(int p) {
  if (tag[p] == -1) return;
  push(p * 2, tag[p]);
  push(p * 2 + 1, tag[p]);
  tag[p] = -1;
}

void build(int l, int r, int p) {
  tag[p] = -1, f[p] = s[p] = 0, len[p] = r - l + 1;
  if (l == r) return;
  int m = (l + r) / 2;
  build(l, m, p * 2);
  build(m + 1, r, p * 2 + 1);
  up(p);
}

void upd(int ql, int qr, int l, int r, int p, int v) {
  // debug(ql, qr, l, r, p, v);
  if (ql <= l && r <= qr) {
    push(p, v);
    return;
  }
  int m = (l + r) / 2;
  if (ql <= m) upd(ql, qr, l, m, p * 2, v);
  if (qr > m) upd(ql, qr, m + 1, r, p * 2 + 1, v);
  up(p);
}

void upd(int l, int r, int p, int x, int v) {
  if (l == r) {
    s[p] = v;
    f[p] = v;
    return;
  }
  down(p);
  int m = (l + r) / 2;
  if (x <= m) upd(l, m, p * 2, x, v);
  else upd(m + 1, r, p * 2 + 1, x, v);
  up(p);
}

ll get_pos(int l, int r, int p, int v) {
  if (l == r) return l;
  down(p);
  int m = (l + r) / 2;
  if (f[p * 2] <= v) {
    return get_pos(m + 1, r, p * 2 + 1, v);
  } else {
    return get_pos(l, m, p * 2, v);
  }
}

void solve() {
  int n;
  cin >> n;
  vi p(n);
  rep(i, n) cin >> p[i];
  vi a(n * 2);
  rep(i, n * 2) a[i] = p[i % n];
  ll res = 0, ans = 0;
  vi vis(n), b(n * 2);
  int mex = 0;
  rep(i, n) {
    vis[a[i]] = 1;
    while (mex < n && vis[mex]) mex += 1;
    b[i] = mex;
    res += b[i];
  }
  cmax(ans, res);
  // for (int i = n; i < n * 2; i++) {
  //   res -= b[i - n];
  //   b[i] = n;
  //   res += b[i];
  //   for (int j = i - 1; j > i - n && b[j] > a[i]; j--) {
  //     res -= b[j] - a[i];
  //     b[j] = a[i];
  //   }
  //   cmax(ans, res);
  // }
  build(0, n * 2, 1);
  rep(i, n) upd(0, n * 2, 1, i, b[i]);
  // debug(s[1]);
  rep(i, n, n * 2) {
    upd(0, n * 2, 1, i, n);
    upd(0, n * 2, 1, i - n, 0);
    int p = get_pos(0, n * 2, 1, a[i]);
    // debug(a[i], p, i - 1);
    upd(p, i - 1, 0, n * 2, 1, a[i]);
    cmax(ans, s[1]);
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