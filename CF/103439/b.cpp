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

int K, n, q, tot, rt[20010], a[4][250010];
vector<int> tr[4];

struct node {
  int l, r, mn[1 << 4], tag[4], cov[4];
  node() { memset(cov, -1, sizeof(cov)); }
} t[2000000];

void apply_add(int k, int p, int v) {
  (~t[k].cov[p] ? t[k].cov[p] : t[k].tag[p]) += v;
  for (int S : tr[p])
    t[k].mn[S] += v;
}

void apply_cov(int k, int p, int v) {
  t[k].cov[p] = v, t[k].tag[p] = 0;
  for (int S : tr[p])
    t[k].mn[S] = t[k].mn[S ^ (1 << p)] + v;
}

void pushdown(int k) {
  int ls = t[k].l, rs = t[k].r;
  t[t[k].l = ++tot] = t[ls], t[t[k].r = ++tot] = t[rs];
  for (int i = 0; i < K; i++) {
    if (~t[k].cov[i])
      apply_cov(t[k].l, i, t[k].cov[i]), apply_cov(t[k].r, i, t[k].cov[i]);
    else if (t[k].tag[i])
      apply_add(t[k].l, i, t[k].tag[i]), apply_add(t[k].r, i, t[k].tag[i]);
    t[k].cov[i] = -1, t[k].tag[i] = 0;
  }
}

void maintain(int k) {
  for (int S = 0; S < 1 << K; S++) {
    t[k].mn[S] = min(t[t[k].l].mn[S], t[t[k].r].mn[S]);
  }
}

#define mid ((l + r) >> 1)
void build(int &k, int l, int r) {
  k = ++tot;
  if (l == r) {
    for (int S = 1; S < 1 << K; S++) {
      int i = __builtin_ctz(S);
      t[k].mn[S] = t[k].mn[S ^ (1 << i)] + a[i][l];
    }
    return;
  }
  build(t[k].l, l, mid), build(t[k].r, mid + 1, r), maintain(k);
}

void modify(int k, int l, int r, int ql, int qr, int p, int v, int op) {
  if (l >= ql && r <= qr)
    return op == 1 ? apply_add(k, p, v) : apply_cov(k, p, v);
  pushdown(k);
  if (mid >= ql)
    modify(t[k].l, l, mid, ql, qr, p, v, op);
  if (mid < qr)
    modify(t[k].r, mid + 1, r, ql, qr, p, v, op);
  maintain(k);
}

int query(int k, int l, int r, int ql, int qr) {
  if (l >= ql && r <= qr)
    return t[k].mn[(1 << K) - 1];
  pushdown(k);
  int ans = INT_MAX;
  if (mid >= ql)
    ans = min(ans, query(t[k].l, l, mid, ql, qr));
  if (mid < qr)
    ans = min(ans, query(t[k].r, mid + 1, r, ql, qr));
  return ans;
}

void solve() {
  cin >> K >> n >> q;
  for (int i = 0; i < K; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i < 1 << K; i++) {
    for (int j = 0; j < K; j++) {
      if (i >> j & 1)
        tr[j].push_back(i);
    }
  }
  build(rt[0], 1, n);
  for (int i = 1, op, lst, p, l, r, x; i <= q; i++) {
    cin >> op >> lst;
    t[rt[i] = ++tot] = t[rt[lst]];
    if (op <= 2) {
      cin >> p >> l >> r >> x;
      modify(rt[i], 1, n, l, r, p - 1, x, op);
    } else {
      cin >> l >> r;
      int ans = query(rt[i], 1, n, l, r);
      cout << ans << "\n";
    }
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