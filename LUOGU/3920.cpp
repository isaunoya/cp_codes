// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
#define pb emplace_back
using namespace std;
using ll = long long;
const int io_size = 1 << 23 | 233;
const int io_limit = 1 << 22;
struct io_in {
  char ch;
#ifndef __WIN64
  char getchar() {
    static char buf[io_size], *p1 = buf, *p2 = buf;

    return (p1 == p2) &&
                   (p2 = (p1 = buf) + fread(buf, 1, io_size, stdin), p1 == p2)
               ? EOF
               : *p1++;
  }
#endif
  template <class T>

  void read(T &x) {
    bool f = 0;
    while ((ch = getchar()) < 48 && ~ch)
      f ^= (ch == 45);

    x = ~ch ? (ch ^ 48) : 0;
    while ((ch = getchar()) > 47)
      x = x * 10 + (ch ^ 48);
    x = f ? -x : x;
  }

  io_in &operator>>(int &x) { return read(x), *this; }

  io_in &operator>>(ll &x) { return read(x), *this; }
} in;

struct io_out {
  char buf[io_size], *s = buf;
  int st[233];

  ~io_out() { flush(); }

  void io_chk() {
    if (s - buf > io_limit)
      flush();
  }

  void flush() { fwrite(buf, 1, s - buf, stdout), fflush(stdout), s = buf; }

  io_out &operator<<(char c) { return *s++ = c, *this; }

  template <class T>

  void write(T x) {
    if (x < 0)
      *s++ = '-', x = -x;
    do {
      st[++st[0]] = x % 10, x /= 10;
    } while (x);
    while (st[0])
      *s++ = st[st[0]--] ^ 48;
  }
  io_out &operator<<(int x) { return write(x), io_chk(), *this; }
  io_out &operator<<(ll x) { return write(x), io_chk(), *this; }
} out;
void cmax(int &x, const int &y) {
  if (x < y)
    x = y;
}
int n;
const int maxn = 1e5 + 51;
const double alpha = 0.8;
const int mod = 1e9;
vector<int> g[maxn];
int fa[maxn], val[maxn];

struct Edge {
  int v, nxt;
} e[maxn << 1];
int head[maxn], cnt = 0;

void add_edge(int u, int v) {
  e[++cnt] = {v, head[u]}, head[u] = cnt;
  e[++cnt] = {u, head[v]}, head[v] = cnt;
}

int f[maxn][19], dep[maxn], len[maxn];
int lca(int x, int y) {
  if (dep[x] < dep[y])
    x ^= y ^= x ^= y;
  for (int i = 17; ~i; i--)
    if (dep[f[x][i]] >= dep[y])
      x = f[x][i];
  if (x == y)
    return x;
  for (int i = 17; ~i; i--)
    if (f[x][i] ^ f[y][i])
      x = f[x][i], y = f[y][i];
  return f[x][0];
}

int dis(int x, int y) { return len[x] + len[y] - 2 * len[lca(x, y)]; }

struct ScapeGoatTree {
  struct Goat {
    int val, sz;
    Goat *ch[2];
    Goat() {}
    bool bad() {
      return ch[0]->sz >= sz * alpha + 5 || ch[1]->sz >= sz * alpha + 5;
    }
  } *tr1[maxn], *tr2[maxn], *pool[maxn << 8], *null, *sta[maxn], mem[maxn << 8];

  int tot, top;

  void init() {
    null = new Goat(), null->ch[0] = null->ch[1] = null,
    null->sz = null->val = 0;
    for (int i = 0; i < (maxn << 8); i++)
      pool[i] = mem + i;
    tot = (maxn << 8) - 1;
    for (int i = 0; i < maxn; i++)
      tr1[i] = tr2[i] = null;
  }

  Goat **insert(Goat *&p, int val) {
    if (p == null) {
      p = pool[tot--], p->ch[0] = p->ch[1] = null;
      p->val = val, p->sz = 1;
      return &null;
    }
    p->sz++;
    Goat **o = insert(p->ch[p->val < val], val);
    if (p->bad())
      o = &p;
    return o;
  }

  int getrk(Goat *p, int val) {
    if (p == null)
      return 0;
    return (p->val >= val) ? getrk(p->ch[0], val)
                           : (getrk(p->ch[1], val) + p->ch[0]->sz + 1);
  }

  void clr(Goat *p) {
    if (p == null)
      return;
    if (p->ch[0] != null)
      clr(p->ch[0]);
    pool[++tot] = p;
    if (p->ch[1] != null)
      clr(p->ch[1]);
  }

  void travel(Goat *p) {
    if (p == null)
      return;
    if (p->ch[0] != null)
      travel(p->ch[0]);
    sta[++top] = p;
    if (p->ch[1] != null)
      travel(p->ch[1]);
  }

  Goat *build(int l, int r) {
    if (l > r)
      return null;
    int mid = l + r >> 1;
    Goat *p = sta[mid];
    p->sz = r - l + 1;
    p->ch[0] = build(l, mid - 1);
    p->ch[1] = build(mid + 1, r);
    return p;
  }

  void rebuild(Goat *&p) { top = 0, travel(p), p = build(1, top); }

  void Insert(Goat *&p, int val) {
    Goat **o = insert(p, val);
    if (*o != null)
      rebuild(*o);
  }
} sgt;

int sz[maxn], mx[maxn], vis[maxn], siz, rt;

void findrt(int u, int fa) {
  sz[u] = 1, mx[u] = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v ^ fa && !vis[v]) {
      findrt(v, u), sz[u] += sz[v], cmax(mx[u], sz[v]);
    }
  }
  cmax(mx[u], siz - sz[u]);
  if (mx[u] < mx[rt])
    rt = u;
}

void dfs(int u, int f, int rt) {
  sgt.Insert(sgt.tr1[rt], dis(u, rt) - val[u]);
  if (fa[rt])
    sgt.Insert(sgt.tr2[rt], dis(u, fa[rt]) - val[u]);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v ^ f && !vis[v])
      dfs(v, u, rt);
  }
}

void solve(int u, int f) {
  int totsz = siz;
  fa[u] = f, vis[u] = 1, dfs(u, 0, u);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!vis[v]) {
      rt = 0, siz = sz[v] > sz[u] ? totsz - sz[u] : sz[v];
      findrt(v, 0), g[u].pb(rt), solve(rt, u);
    }
  }
}

void recover(int x) {
  ++siz, vis[x] = 0, sgt.clr(sgt.tr1[x]), sgt.clr(sgt.tr2[x]);
  sgt.tr1[x] = sgt.tr2[x] = sgt.null;
  for (int v : g[x])
    recover(v);
  g[x].clear();
}

void rebuild(int x) {
  siz = 0, recover(x), rt = 0, findrt(x, 0);
  if (fa[x])
    for (int i = 0, lim = g[fa[x]].size(); i < lim; i++)
      if (g[fa[x]][i] == x)
        g[fa[x]][i] = rt;
  solve(rt, fa[x]);
}

ll ans = 0;
int insert(int x) {
  for (int i = x; fa[i]; i = fa[i]) {
    int ds = val[x] - dis(x, fa[i]) + 1;
    ans += sgt.getrk(sgt.tr1[fa[i]], ds) - sgt.getrk(sgt.tr2[i], ds);
  }
  sgt.Insert(sgt.tr1[x], -val[x]);
  for (int i = x; fa[i]; i = fa[i]) {
    int ds = dis(fa[i], x) - val[x];
    sgt.Insert(sgt.tr1[fa[i]], ds);
    sgt.Insert(sgt.tr2[i], ds);
  }
  int res = 0;
  for (int i = x; fa[i]; i = fa[i])
    if (sgt.tr1[i]->sz >= sgt.tr1[fa[i]]->sz * alpha + 5)
      res = fa[i];
  return res;
}

signed main() {
  // code begin.
  int FUCK;
  in >> FUCK >> n, mx[rt = 0] = 1e9, sgt.init();
  rep(i, 1, n) {
    int qwq;
    in >> fa[i] >> qwq >> val[i];
    f[i][0] = fa[i] ^ (ans % mod), fa[i] = f[i][0];
    dep[i] = dep[fa[i]] + 1, len[i] = len[fa[i]] + qwq, vis[i] = 1;
    if (fa[i])
      g[fa[i]].pb(i), add_edge(f[i][0], i);
    for (int j = 1; (1 << j) + 1 <= dep[i]; j++)
      f[i][j] = f[f[i][j - 1]][j - 1];
    int x = insert(i);
    if (x)
      rebuild(x);
    out << ans << '\n';
  }
  return 0;
  // code end.
}