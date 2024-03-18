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

const int N = 1e5 + 5;
ll F[N], f[N * 4];
ll G[N], g[N * 4];
ll sf[N * 4], sg[N * 4];
void upf(int p) {
  f[p] = max(f[p * 2], f[p * 2 + 1]);
  sf[p] = sf[p * 2] + sf[p * 2 + 1];
}
void upg(int p) {
  g[p] = max(g[p * 2], g[p * 2 + 1]);
  sg[p] = sg[p * 2] + sg[p * 2 + 1];
}
ll tagf[N * 4], tagg[N * 4];
int len[N * 4];
void build(int l, int r, int p) {
  tagf[p] = tagg[p] = 0;
  len[p] = r - l + 1;
  if (l == r) {
    f[p] = F[l];
    g[p] = G[l];
    sf[p] = F[l];
    sg[p] = G[l];
    return;
  }
  int m = (l + r) / 2;
  build(l, m, p * 2);
  build(m + 1, r, p * 2 + 1);
  upf(p);
  upg(p);
}
void puf(int p, ll v) {
  tagf[p] = v;
  f[p] = v;
  sf[p] = 1ll * v * len[p];
}
void downf(int p) {
  if (tagf[p]) {
    puf(p * 2, tagf[p]);
    puf(p * 2 + 1, tagf[p]);
    tagf[p] = 0;
  }
}
void pug(int p, ll v) {
  tagg[p] = v;
  g[p] = v;
  sg[p] = 1ll * v * len[p];
}
void downg(int p) {
  if (tagg[p]) {
    pug(p * 2, tagg[p]);
    pug(p * 2 + 1, tagg[p]);
    tagg[p] = 0;
  }
}
void updf(int ql, int qr, int l, int r, int p, ll v) {
  if (ql <= l && r <= qr) {
    puf(p, v);
    return;
  }
  downf(p);
  int m = (l + r) / 2;
  if (ql <= m)
    updf(ql, qr, l, m, p * 2, v);
  if (qr > m)
    updf(ql, qr, m + 1, r, p * 2 + 1, v);
  upf(p);
}
void updg(int ql, int qr, int l, int r, int p, ll v) {
  if (ql <= l && r <= qr) {
    pug(p, v);
    return;
  }
  downg(p);
  int m = (l + r) / 2;
  if (ql <= m)
    updg(ql, qr, l, m, p * 2, v);
  if (qr > m)
    updg(ql, qr, m + 1, r, p * 2 + 1, v);
  upg(p);
}
int max_rightF(int l, int r, int p, ll val) {
  if (l == r) {
    return l;
  }
  downf(p);
  int m = (l + r) / 2;
  if (f[p * 2] >= val) {
    return max_rightF(l, m, p * 2, val);
  } else {
    return max_rightF(m + 1, r, p * 2 + 1, val);
  }
}
int min_leftG(int l, int r, int p, ll val) {
  if (l == r) {
    return l;
  }
  downg(p);
  int m = (l + r) / 2;
  if (g[p * 2 + 1] >= val) {
    return min_leftG(m + 1, r, p * 2 + 1, val);
  } else {
    return min_leftG(l, m, p * 2, val);
  }
}
ll queryf(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    return f[p];
  }
  downf(p);
  int m = (l + r) / 2;
  ll res = 0;
  if (ql <= m)
    cmax(res, queryf(ql, qr, l, m, p * 2));
  if (qr > m)
    cmax(res, queryf(ql, qr, m + 1, r, p * 2 + 1));
  return res;
}
ll queryg(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    return g[p];
  }
  downg(p);
  int m = (l + r) / 2;
  ll res = 0;
  if (ql <= m)
    cmax(res, queryg(ql, qr, l, m, p * 2));
  if (qr > m)
    cmax(res, queryg(ql, qr, m + 1, r, p * 2 + 1));
  return res;
}
ll querysf(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    return sf[p];
  }
  downf(p);
  int m = (l + r) / 2;
  ll res = 0;
  if (ql <= m)
    res += querysf(ql, qr, l, m, p * 2);
  if (qr > m)
    res += querysf(ql, qr, m + 1, r, p * 2 + 1);
  return res;
}
ll querysg(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    return sg[p];
  }
  downg(p);
  int m = (l + r) / 2;
  ll res = 0;
  if (ql <= m)
    res += querysg(ql, qr, l, m, p * 2);
  if (qr > m)
    res += querysg(ql, qr, m + 1, r, p * 2 + 1);
  return res;
}

void solve() {
  int n;
  cin >> n;
  vc<ll> a(n);
  rep(i, n) cin >> a[i];
  int p = 0;
  rep(i, n) if (a[p] < a[i]) p = i;
  ll s = accumulate(all(a), 0LL);
  F[0] = a[0];
  rep(i, 1, n) cmax(F[i] = a[i], F[i - 1]);
  G[n - 1] = a[n - 1];
  for (int i = n - 2; i >= 0; i--)
    cmax(G[i] = a[i], G[i + 1]);
  build(0, n - 1, 1);
  int q;
  cin >> q;
  while (q--) {
    int i, x;
    cin >> i >> x;
    --i;
    ll v = a[i] + x;
    // int l = i - 1, r = n;
    // while (r - l > 1) {
    //   int m = (l + r) / 2;
    //   if (queryf(i, m, 0, n - 1, 1) <= v) {
    //     l = m;
    //   } else {
    //     r = m;
    //   }
    // }
    int pos = max_rightF(0, n - 1, 1, v) - 1;
    if (f[1] <= v) pos = n - 1;
    // debug(l, pos);
    if (i <= pos)
      updf(i, pos, 0, n - 1, 1, v);
    // l = -1;
    // r = i + 1;
    // while (r - l > 1) {
    //   int m = (l + r) / 2;
    //   if (queryg(m, i, 0, n - 1, 1) <= v) {
    //     r = m;
    //   } else {
    //     l = m;
    //   }
    // }
    pos = min_leftG(0, n - 1, 1, v) + 1;
    if (g[1] <= v) pos = 0;
    // debug(r, pos);
    if (pos <= i)
      updg(pos, i, 0, n - 1, 1, v);
    s += x;
    a[i] += x;
    if (a[i] > a[p]) {
      p = i;
    }
    ll res = querysf(0, p, 0, n - 1, 1);
    if (p < n - 1)
      res += querysg(p + 1, n - 1, 0, n - 1, 1);
    res -= s;
    cout << res << "\n";
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