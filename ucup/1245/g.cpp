#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <typename T> ostream &operator<<(ostream &out, const vector<T> &x) {
  if (x.empty())
    return out << "[]";
  out << '[' << x[0];
  for (int len = x.size(), i = 1; i < len; i++)
    out << ',' << x[i];
  return out << ']';
}
template <typename T> vector<T> ary(const T *a, int l, int r) {
  return vector<T>{a + l, a + 1 + r};
}
template <typename T> void debug(T x) { cerr << x << '\n'; }
template <typename T, typename... S> void debug(T x, S... y) {
  cerr << x << ' ', debug(y...);
}
const int N = 2e5 + 10, E = 4e7 + 10;
int T, n, m, k;
struct edges {
  int u, v, w;
} e[E];
int p[N];
ll ans;
vector<int> to[N];
int cnt, fa[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool merge(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return 0;
  return cnt--, fa[x] = y, 1;
}
int vis[N], cur[N];
void link(int lim) {
  for (int i = 1; i <= n; i++) {
    for (int v : to[i])
      vis[v] = 1;
    int t = p[i - 1] + 1;
    for (int l; (l = cur[i]) >= 1; cur[i]--) {
      int d = -1;
      if (!vis[l])
        d = t - p[l];
      else if (p[i] > t)
        d = t - p[l];
      else if (p[l - 1] + 1 < p[l])
        d = t - p[l] + 1;
      else
        continue;
      if (d > lim)
        break;
      if (merge(l, i))
        ans += d;
    }
    for (int v : to[i])
      vis[v] = 0;
  }
}
void get() {
  scanf("%d%d", &m, &k);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    p[++n] = e[i].u, p[++n] = e[i].v;
  }
  sort(p + 1, p + 1 + n), n = unique(p + 1, p + 1 + n) - p - 1;
  if (p[n] != m)
    p[++n] = m;
  auto trs = [&](int &x) { x = lower_bound(p + 1, p + 1 + n, x) - p; };
  for (int i = 1; i <= k; i++) {
    trs(e[i].u), trs(e[i].v);
    to[e[i].v].push_back(e[i].u);
  }
  for (int i = 1; i <= n; i++) {
    ans += p[i] - p[i - 1] - 1;
    cnt -= p[i] - p[i - 1] - 1;
  }
  for (int i = 1; i <= n; i++)
    cur[i] = i - 1;
  iota(fa, fa + 1 + n, 0);
  sort(e + 1, e + 1 + k, [](edges x, edges y) { return x.w < y.w; });
  cnt = n;
  int i = 1;
  for (int x = 0, lim = sqrt(k * 2) + 10; cnt > 1 && x < lim; x++) {
    for (; i <= k && e[i].w <= x; i++)
      if (merge(e[i].u, e[i].v))
        ans += e[i].w;
    link(x);
  }
  for (; i <= k; i++)
    if (merge(e[i].u, e[i].v))
      ans += e[i].w;
  printf("%lld\n", ans);
}
void clr() {
  for (int i = 1; i <= n; i++)
    to[i].clear();
  n = ans = 0;
}
int main() {
  for (scanf("%d", &T); T--; clr())
    get();
  return 0;
}