#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

const int B = 1 << 25;
struct streambufcin {
  std::streambuf *in;
  char buf[B], *bg, *ed, ch;
  streambufcin() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    in = std::cin.rdbuf();
    bg = ed = NULL;
  }
  char getchar() {
    return (bg == ed) && (ed = (bg = buf) + in->sgetn(buf, B), bg == ed)
               ? -1
               : *bg++;
  }
  streambufcin &operator>>(char &c) {
    for (c = getchar(); isspace(c); c = getchar())
      ;
    return *this;
  }
  template <class T> streambufcin &operator>>(T &x) {
    bool neg = false;
    for (ch = getchar(); !isdigit(ch); ch = getchar())
      if (ch == '-')
        neg = true;
    for (x = 0; isdigit(ch); ch = getchar())
      x = x * 10 + ch - 48;
    if (neg)
      x = -x;
    return *this;
  }
} in;

const int N = 1e5;
struct unionfind {
  int p[N];
  unionfind() {}
  void init(int n) { memset(p, -1, n << 2); }
  int root(int x) { return p[x] < 0 ? x : p[x] = root(p[x]); }
  bool same(int x, int y) { return root(x) == root(y); }
  void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x != y) {
      if (p[x] < p[y]) {
        swap(x, y);
      }
      p[y] += p[x];
      p[x] = y;
    }
  }
  int size(int x) { return -p[root(x)]; }
} f;

int ans = 0;
int mx[N * 4], mn[N * 4], tag[N * 4];
void build(int l, int r, int p) {
  mx[p] = mn[p] = tag[p] = -2;
  if (l == r)
    return;
  int m = (l + r) / 2;
  build(l, m, p * 2);
  build(m + 1, r, p * 2 + 1);
}

void ps(int p, int v) { mn[p] = mx[p] = tag[p] = v; }
void psd(int p) {
  if (tag[p] != -2) {
    ps(p * 2, tag[p]), ps(p * 2 + 1, tag[p]);
    tag[p] = -2;
  }
}
void pu(int p) {
  cmax(mx[p] = mx[p * 2], mx[p * 2 + 1]);
  cmin(mn[p] = mn[p * 2], mn[p * 2 + 1]);
}

int ql, qr, v;
void mdf(int l, int r, int p) {
  if (ql <= l && r <= qr) {
    ps(p, v);
    return;
  }
  psd(p);
  int m = (l + r) / 2;
  if (ql <= m)
    mdf(l, m, p * 2);
  if (qr > m)
    mdf(m + 1, r, p * 2 + 1);
  pu(p);
}
void mdf(int L, int R, int l, int r, int p, int vv) {
  ql = L, qr = R, v = vv;
  mdf(l, r, p);
}

void get(int l, int r, int p) {
  if (mx[p] < 0)
    return;
  if (ql <= l && r <= qr && mx[p] == mn[p]) {
    if (!f.same(mx[p], v))
      ans--, f.unite(mx[p], v);
    return;
  }
  psd(p);
  int m = (l + r) / 2;
  if (ql <= m)
    get(l, m, p * 2);
  if (qr > m)
    get(m + 1, r, p * 2 + 1);
  pu(p);
}
void get(int L, int R, int l, int r, int p, int vv) {
  ql = L, qr = R, v = vv;
  get(l, r, p);
}
ll s[N + 2], c[N + 2];
vc<array<int, 3>> bar[N + 2], db[N + 2];
vc<pii> line[N + 2], dl[N + 2];
void solve() {
  int n, M, q;
  in >> n >> M >> q;
  rp(i, n) s[i] = c[i] = 0, bar[i].clear(), db[i].clear(), line[i].clear(), dl[i].clear();
  rp(i, q) {
    int r1, c1, r2, c2;
    in >> r1 >> c1 >> r2 >> c2;
    --r1, --r2;
    if (r1 == r2) {
      bar[r1].pb(array<int, 3>{c1, c2, i});
      s[r1] += c2 - c1 + 1;
      db[r1 + 1].pb(array<int, 3>{c1, c2, -1});
    } else if (c1 == c2) {
      c[r1] += 1;
      c[r2 + 1] -= 1;
      line[r1].pb(c1, i);
      dl[r2 + 1].pb(c1, -1);
    } else {
      assert(0);
    }
  }
  build(1, M, 1);
  ans = 0;
  f.init(q);
  ll tmp = 0;
  rp(i, n) {
    for (auto arr : bar[i]) {
      auto [l, r, col] = arr;
      ans++;
      get(l, r, 1, M, 1, col);
    }
    for (auto [x, col] : line[i]) {
      ans++;
      get(x, x, 1, M, 1, col);
    }
    for (auto arr : db[i]) {
      auto [l, r, col] = arr;
      mdf(l, r, 1, M, 1, col);
    }
    for (auto [x, col] : dl[i]) {
      mdf(x, x, 1, M, 1, col);
    }
    for (auto [x, col] : line[i]) {
      col = f.root(col);
      mdf(x, x, 1, M, 1, col);
      get(max(x - 1, 1), min(x + 1, M), 1, M, 1, col);
    }
    for (auto arr : bar[i]) {
      auto [l, r, col] = arr;
      col = f.root(col);
      if (l - 1 >= 1) {
        get(l - 1, l - 1, 1, M, 1, col);
      }
      if (r + 1 <= M) {
        get(r + 1, r + 1, 1, M, 1, col);
      }
      mdf(l, r, 1, M, 1, col);
    }
    if (i) {
      s[i] += s[i - 1];
      c[i] += c[i - 1];
    }
    tmp += c[i];
    cout << s[i] + tmp << " " << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  in >> t;
  while (t--) {
    solve();
  }
  return 0;
}