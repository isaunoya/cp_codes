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

const int N = 5e5 + 5;
int c, n, m, q, x[N], y[N], f[N], g[N], mn[N];
bool solve(int *f, int *g, int n, int m) {
  if (f[1] < g[1])
    swap(f, g), swap(n, m);
  mn[0] = INT_MAX;
  for (int i = 1; i <= m; ++i)
    mn[i] = min(mn[i - 1], g[i]);
  for (int i = 1, lm = 0, j = 1; i <= n; ++i) {
    lm = max(lm, f[i]);
    while (j <= m && g[j] < lm)
      ++j;
    if (j <= m && f[i] <= mn[j])
      return 0;
  }

  return 1;
}

bool work() {
  if (1ll * (f[1] - g[1]) * (f[n] - g[m]) <= 0)
    return 0;
  if (!solve(f, g, n, m))
    return 0;
  reverse(f + 1, f + n + 1);
  reverse(g + 1, g + m + 1);
  return solve(f, g, n, m);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> c >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
    cin >> x[i];
  for (int i = 1; i <= m; ++i)
    cin >> y[i];
  memcpy(f + 1, x + 1, 4 * n);
  memcpy(g + 1, y + 1, 4 * m);
  cout << work();
  for (int kx, ky; q--;) {
    cin >> kx >> ky;
    memcpy(f + 1, x + 1, 4 * n);
    memcpy(g + 1, y + 1, 4 * m);
    for (int i = 1, p, v; i <= kx; ++i)
      cin >> p >> v, f[p] = v;
    for (int i = 1, p, v; i <= ky; ++i)
      cin >> p >> v, g[p] = v;
    cout << work();
  }
  return 0;
}