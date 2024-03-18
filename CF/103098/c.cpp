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
  int n1, m1, n2, m2;
  cin >> n1 >> m1 >> n2 >> m2;
  unionfind f1(n1);
  vc<array<int, 3>> e1(m1);
  rep(i, m1) { cin >> e1[i][1] >> e1[i][2] >> e1[i][0]; }
  sort(all(e1));
  vi r1, r2;
  for (auto [w, u, v] : e1) {
    if (f1.same(u, v))
      continue;
    f1.unite(u, v);
    r1.pb(w);
  }
  unionfind f2(n2);
  vc<array<int, 3>> e2(m2);
  rep(i, m2) { cin >> e2[i][1] >> e2[i][2] >> e2[i][0]; }
  sort(all(e2));
  for (auto [w, u, v] : e2) {
    if (f2.same(u, v))
      continue;
    f2.unite(u, v);
    r2.pb(w);
  }
  ll res = 0;
  rep(i, r1.size()) res += r1[i];
  rep(i, r2.size()) res += r2[i];
  // n1-1+n2-1+(n1-1)(n2-1)
  int j = 0;
  ll s = 0;
  for (int i = 0; i < sz(r1); i++) {
    while (j < sz(r2) && r2[j] <= r1[i]) {
      s += r2[j++];
    }
    int rem = sz(r2) - j;
    res += s + 1ll * rem * r1[i];
  }
  cout << res << "\n";
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