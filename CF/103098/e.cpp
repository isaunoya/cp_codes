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

int n, q;
const int N = 131072;
const int P = 1e9 + 7;
int a[N], b[N];
int cnt[N * 2];
int p[N * 2][2];

void pu(int x) {
  cnt[x] = cnt[x * 2] ^ cnt[x * 2 + 1];
  int sz = cnt[x * 2];
  if (sz % 2 == 0) {
    p[x][0] = p[x * 2][0] + p[x * 2 + 1][0];
    p[x][1] = p[x * 2][1] + p[x * 2 + 1][1];
  } else {
    p[x][0] = p[x * 2][0] + p[x * 2 + 1][1];
    p[x][1] = p[x * 2][1] + p[x * 2 + 1][0];
  }
  if (p[x][0] >= P) {
    p[x][0] -= P;
  }
  if (p[x][1] >= P) {
    p[x][1] -= P;
  }
}

void upd(int x, int v) {
  const int &value = b[x];
  x += N;
  int &c = cnt[x];
  if (v == 1) {
    c ^= 1;
    p[x][c] += value;
    if (p[x][c] >= P) {
      p[x][c] -= P;
    }
  } else {
    p[x][c] -= value;
    if (p[x][c] < 0) {
      p[x][c] += P;
    }
    c ^= 1;
  }
  while (x >>= 1)
    pu(x);
}

const int B = 400;
void solve() {
  cin >> n >> q;
  rep(i, n) cin >> a[i], b[i] = a[i];
  sort(b, b + n);
  int m = unique(b, b + n) - b;
  rep(i, n) a[i] = lower_bound(b, b + m, a[i]) - b;
  vc<array<int, 3>> que(q);
  rep(i, q) {
    int l, r;
    cin >> l >> r;
    que[i] = array<int, 3>{l, r, i};
  }
  sort(all(que), [&](auto x, auto y) { int bx = x[0] / B, by = y[0] / B; return (bx == by) ? ((bx & 1) ? x[1] < y[1] : x[1] > y[1]) : bx < by; });
  vi ans(q);
  int l = 0, r = -1;
  for (auto [ql, qr, i] : que) {
    while (l < ql)
      upd(a[l++], -1);
    while (l > ql)
      upd(a[--l], 1);
    while (r < qr)
      upd(a[++r], 1);
    while (r > qr)
      upd(a[r--], -1);
    ans[i] = p[1][1];
  }
  rep(i, q) cout << ans[i] << "\n";
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