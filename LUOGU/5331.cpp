#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, j, k) for (int i = j; i <= k; i++)
void read(int &x) {
  char c = x = 0;
  bool f = 1;
  while (c < '0' || c > '9') {
    if (c == '-')
      f = 0;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c & 15);
    c = getchar();
  }
  x = f ? x : -x;
}
const int N = 2e3 + 10, M = 4e5 + 10;
int n, W, s, t, a[N], A[N], rt[N][2], id;
namespace MCMF {
void cmax(int &x, int y) {
  if (x < y)
    x = y;
}
void cmin(int &x, int y) {
  if (x > y)
    x = y;
}
struct Edge {
  int v, nxt, f, c;
} e[M << 1];
int ecnt = 1, head[N << 5], pre[N << 5], dis[N << 5], vis[N << 5];
void add(int u, int v, int flow, int cost) {
  e[++ecnt] = {v, head[u], flow, cost};
  head[u] = ecnt;
  e[++ecnt] = {u, head[v], 0, -cost};
  head[v] = ecnt;
}
bool spfa(int s) {
  memset(dis, 0x3f, sizeof(dis));
  queue<int> q;
  dis[s] = 0;
  q.push(s);
  while (q.size()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (dis[v] > dis[u] + e[i].c && e[i].f) {
        dis[v] = dis[u] + e[i].c;
        pre[v] = i;
        if (!vis[v]) {
          vis[v] = 1;
          q.push(v);
        }
      }
    }
  }
  return (dis[t] != 0x3f3f3f3f);
}
ll upd(ll &maxflow) {
  int p = 0, mn = 1e9, cost = 0;
  for (int u = t; u ^ s; u = e[p ^ 1].v)
    cmin(mn, e[p = pre[u]].f);
  for (int u = t; u ^ s; u = e[p ^ 1].v) {
    e[p = pre[u]].f -= mn;
    e[p ^ 1].f += mn;
    cost += e[p].c * mn;
  }
  return maxflow += mn, cost;
}
void EK(ll &maxflow, ll &mincost) {
  while (spfa(s))
    mincost += upd(maxflow);
}
} // namespace MCMF
namespace SegMentTree {
int cnt, ls[N << 5], rs[N << 5], _id[N << 5];
void build(int pos, int l, int r, int pre, int &p, int to) {
  ls[p = ++cnt] = ls[pre];
  rs[cnt] = rs[pre];
  _id[cnt] = ++id;
  if (l == r) {
    MCMF ::add(_id[p], to, 1, -A[l]);
    return;
  }
  int mid = l + r >> 1;
  (pos <= mid) ? build(pos, l, mid, ls[pre], ls[p], to)
               : build(pos, mid + 1, r, rs[pre], rs[p], to);
  if (ls[p])
    MCMF ::add(_id[p], _id[ls[p]], 1e9, 0);
  if (rs[p])
    MCMF ::add(_id[p], _id[rs[p]], 1e9, 0);
}
void _build(int pos, int l, int r, int pre, int &p, int to) {
  ls[p = ++cnt] = ls[pre];
  rs[cnt] = rs[pre];
  _id[cnt] = ++id;
  if (l == r) {
    MCMF ::add(_id[p], to, 1, A[l]);
    return;
  }
  int mid = l + r >> 1;
  (pos <= mid) ? _build(pos, l, mid, ls[pre], ls[p], to)
               : _build(pos, mid + 1, r, rs[pre], rs[p], to);
  if (ls[p])
    MCMF ::add(_id[p], _id[ls[p]], 1e9, 0);
  if (rs[p])
    MCMF ::add(_id[p], _id[rs[p]], 1e9, 0);
}
void upd(int a, int b, int l, int r, int p, int from, int cost) {
  if (!p) {
    return;
  }
  if (a <= l && r <= b) {
    MCMF ::add(from, _id[p], 1, cost);
    return;
  }
  int mid = l + r >> 1;
  if (a <= mid)
    upd(a, b, l, mid, ls[p], from, cost);
  if (b > mid)
    upd(a, b, mid + 1, r, rs[p], from, cost);
}
void _upd(int a, int b, int l, int r, int p, int from, int cost) {
  if (!p) {
    return;
  }
  if (a <= l && r <= b) {
    MCMF ::add(from, _id[p], 1, -cost);
    return;
  }
  int mid = l + r >> 1;
  if (a <= mid)
    _upd(a, b, l, mid, ls[p], from, cost);
  if (b > mid)
    _upd(a, b, mid + 1, r, rs[p], from, cost);
}
} // namespace SegMentTree
signed main() {
  read(n);
  read(W);
  s = n * 2 + 1;
  t = id = s + 1;
  rep(i, 1, n) {
    read(a[i]);
    A[i] = a[i];
  }
  sort(A + 1, A + n + 1);
  int len = unique(A + 1, A + n + 1) - A - 1;
  rep(i, 1, n) { a[i] = lower_bound(A + 1, A + len + 1, a[i]) - A; }
  rep(i, 1, n) {
    MCMF ::add(s, i + n, 1, 0);
    MCMF ::add(i + n, t, 1, W);
    MCMF ::add(i, t, 1, 0);
  }
  rep(i, 1, n) {
    SegMentTree ::build(a[i], 1, len, rt[i - 1][0], rt[i][0], i);
    SegMentTree ::_build(a[i], 1, len, rt[i - 1][1], rt[i][1], i);
  }
  rep(i, 2, n) {
    SegMentTree ::upd(1, a[i], 1, len, rt[i - 1][0], i + n, A[a[i]]);
    SegMentTree ::_upd(a[i] + 1, len, 1, len, rt[i - 1][1], i + n, A[a[i]]);
  }
  ll maxflow, mincost;
  maxflow = mincost = 0;
  MCMF ::EK(maxflow, mincost);
  printf("%lld\n", mincost);
  return 0;
}
