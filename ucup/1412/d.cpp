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

const int N = 1048576;
int isprime[N];
int prime[N];
int d[N];
vector<pair<int, int>> edge[60];
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
  int l, r;
  cin >> l >> r;
  for (int i = 0; i < 60; i++) {
    edge[i].clear();
  }
  for (int x = 1; x <= r; x++) {
    int mn = (l + x - 1) / x * x;
    for (int j = (l + x - 1) / x * x; j <= r; j += x) {
      if (d[mn] > d[j]) {
        mn = j;
      }
    }
    for (int j = (l + x - 1) / x * x; j <= r; j += x) {
      edge[d[j] + d[mn] - d[x]].pb(j, mn);
    }
  }
  unionfind f(r + 1);
  ll ans = 0;
  rep(i, 60) {
    for (auto [x, y] : edge[i]) {
      if (!f.same(x, y)) {
        ans += i;
        f.unite(x, y);
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  rep(i, 2, N) isprime[i] = 1;
  rep(i, 2, N) {
    if (isprime[i]) {
      d[i] += 1;
      for (int j = i * 2; j < N; j += i) {
        d[j] += 1;
        isprime[j] = 0;
      }
    }
  }
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}