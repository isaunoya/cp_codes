#include <algorithm>
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
  int n, m;
  cin >> n >> m;
  unionfind f(n * 2);
  rep(i, m) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    f.unite(u * 2 + 1, v * 2);
    debug("unite", u * 2 + 1, v * 2);
  }
  vi deg(n * 2);
  vc<vi> g(n * 2);
  rep(i, n) {
    int u = f.root(i * 2);
    int v = f.root(i * 2 + 1);
    deg[v] += 1;
    g[u].pb(v);
  }
  vi val(n * 2, -1);
  queue<int> q;
  int c = 0;
  rep(i, n * 2) if (deg[i] == 0) q.emplace(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    val[u] = c++;
    for (auto v : g[u])
      if (--deg[v] == 0)
        q.emplace(v);
  }
  if (*min_element(all(val)) == -1) {
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
  rep(i, n) cout << val[f.root(i * 2 + 1)] - val[f.root(i * 2)]
                 << " \n"[i + 1 == n];
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