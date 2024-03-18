#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define eb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  if (x > y)
    x = y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  if (x < y)
    x = y;
}
using ll = long long;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

struct unionfind {
  vector<int> p;
  unionfind(int N) { p = vector<int>(N, -1); }
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
};
void solve() {
  int n;
  cin >> n;
  vector a(n, 0);
  rep(i, 0, n) { cin >> a[i]; }
  sort(all(a));
  a.resize(unique(all(a)) - a.begin());
  n = a.size();
  vector<tuple<int, int, int>> v;
  int mx = a.back();
  rep(u, 0, n) {
    int i = a[u];
    for (int j = i; j <= mx; j += i) {
      int p = lower_bound(a.begin() + u + 1, a.end(), j) - a.begin();
      if (p == n) {
        break;
      }
      int k = a[p];
      if (j <= k && k < j + i) {
        v.eb(u, p, k - j);
      }
    }
  }
  sort(all(v), [&](auto x, auto y) { return get<2>(x) < get<2>(y); });
  unionfind f(n);
  long long ans = 0;
  for (auto [x, y, z] : v) {
    if (f.same(x, y)) {
      continue;
    }
    f.unite(x, y);
    ans += z;
  }
  cout << ans << "\n";
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