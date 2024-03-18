#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template <typename T> bool chkmax(T &x, T y) { return x < y ? x = y, 1 : 0; }
template <typename T> bool chkmin(T &x, T y) { return x > y ? x = y, 1 : 0; }

int readint() {
  int x = 0, f = 1;
  char ch = getchar();

  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;

    ch = getchar();
  }

  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }

  return x * f;
}

int n, m, tot;
int du[4200005], v[240005], nxt[240005], h[120005], dep[120005], f[120005][17],
    lg2[120005], q[4200005];
vector<int> adj[4200005];
pii a[120005];

int id(int x, int y, int t) { return m + t * n * 17 + (x - 1) * 17 + y + 1; }

void addedge(int x, int y) {
  v[++tot] = y;
  nxt[tot] = h[x];
  h[x] = tot;
  v[++tot] = x;
  nxt[tot] = h[y];
  h[y] = tot;
}

void dfs(int u) {
  for (int i = 1; i <= 16; i++)
    f[u][i] = f[f[u][i - 1]][i - 1];

  for (int p = h[u]; p; p = nxt[p]) {
    if (v[p] == f[u][0])
      continue;

    f[v[p]][0] = u, dep[v[p]] = dep[u] + 1;
    dfs(v[p]);
  }
}

int lca(int x, int y) {
  if (dep[x] < dep[y])
    swap(x, y);

  for (int i = 16; i >= 0; i--)
    if (dep[f[x][i]] >= dep[y])
      x = f[x][i];

  if (x == y)
    return x;

  for (int i = 16; i >= 0; i--)
    if (f[x][i] != f[y][i])
      x = f[x][i], y = f[y][i];

  return f[x][0];
}

int jump(int x, int d) {
  for (int i = 16; i >= 0; i--)
    if (d & (1 << i))
      x = f[x][i];

  return x;
}

void add1(int x, int y, int i) {
  int k = lg2[dep[x] - dep[y] + 1];
  adj[id(x, k, 1)].pb(i);
  du[i]++;
  adj[id(jump(x, dep[x] - dep[y] - (1 << k) + 1), k, 1)].pb(i);
  du[i]++;
}

void add0(int x, int y, int i) {
  int k = lg2[dep[x] - dep[y] + 1];
  adj[i].pb(id(x, k, 0));
  du[id(x, k, 0)]++;
  int t = jump(x, dep[x] - dep[y] - (1 << k) + 1);
  adj[i].pb(id(t, k, 0));
  du[id(t, k, 0)]++;
}

void solve() {
  n = readint();

  for (int i = 1; i <= n; i++)
    h[i] = 0;

  tot = 0;

  for (int i = 1; i < n; i++)
    addedge(readint(), readint());

  dep[1] = 1;
  dfs(1);
  m = readint();

  for (int i = 1; i <= n * 17 * 2 + m; i++)
    du[i] = 0, adj[i].clear();

  for (int i = 2; i <= n; i++)
    lg2[i] = lg2[i >> 1] + 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 16; j++) {
      adj[id(i, j, 0)].pb(id(i, j - 1, 0)), du[id(i, j - 1, 0)]++;

      if (f[i][j - 1])
        adj[id(i, j, 0)].pb(id(f[i][j - 1], j - 1, 0)),
            du[id(f[i][j - 1], j - 1, 0)]++;

      adj[id(i, j - 1, 1)].pb(id(i, j, 1)), du[id(i, j, 1)]++;

      if (f[i][j - 1])
        adj[id(f[i][j - 1], j - 1, 1)].pb(id(i, j, 1)), du[id(i, j, 1)]++;
    }
  }

  for (int i = 1; i <= m; i++) {
    a[i].fi = readint(), a[i].se = readint();
    int u = a[i].fi, v = a[i].se, l = lca(u, v);
    adj[i].pb(id(u, 0, 1));
    du[id(u, 0, 1)]++;
    adj[id(v, 0, 0)].pb(i);
    du[i]++;

    if (u != l && v != l) {
      add1(f[u][0], l, i);
      add1(v, l, i);
      add0(u, l, i);
      add0(f[v][0], l, i);
    } else if (u == l) {
      add1(v, jump(v, dep[v] - dep[u] - 1), i);
      add0(f[v][0], u, i);
    } else {
      add1(f[u][0], v, i);
      add0(u, jump(u, dep[u] - dep[v] - 1), i);
    }
  }

  int front = 0, rear = 0;

  for (int i = 1; i <= m + n * 17 * 2; i++)
    if (!du[i])
      q[rear++] = i;

  while (front < rear) {
    int t = q[front++];

    for (auto v : adj[t])
      if (!(--du[v]))
        q[rear++] = v;
  }

  if (rear != m + n * 17 * 2)
    printf("No\n");
  else
    printf("Yes\n");
}

int main() {
  int T = readint();

  while (T--)
    solve();

  return 0;
}