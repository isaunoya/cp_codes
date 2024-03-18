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

void solve() {
  int n, k;
  cin >> n >> k;
  vi a(k);
  rep(i, k) {
    cin >> a[i];
    --a[i];
  }
  vc<vi> g(n);
  rep(i, n - 1) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    g[u].pb(v);
    g[v].pb(u);
  }
  queue<int> q;
  vi d(n, -1);
  d[a[0]] = 1;
  q.emplace(a[0]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (d[v] == -1) {
        d[v] = d[u] + 1;
        q.emplace(v);
      }
    }
  }
  int r = a[0];
  rep(i, k) if (d[r] < d[a[i]]) r = a[i];
  rep(i, n) d[i] = -1;
  d[r] = 0;
  q.emplace(r);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (d[v] == -1) {
        d[v] = d[u] + 1;
        q.emplace(v);
      }
    }
  }
  int r2 = a[0];
  rep(i, k) if (d[r2] < d[a[i]]) r2 = a[i];
  vi d2(n, -1);
  d2[r2] = 0;
  q.emplace(r2);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (d2[v] == -1) {
        d2[v] = d2[u] + 1;
        q.emplace(v);
      }
    }
  }
  vi ans;
  rep(i, n) {
    // debug(i + 1, max(d[i], d2[i]));
    ans.pb(max(d[i], d2[i]));
  }
  if (ans.empty())
    cout << 0 << "\n";
  else
    cout << *min_element(all(ans)) << "\n";
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