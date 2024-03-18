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
  int n, m;
  cin >> n >> m;
  vi lst(m, -1);
  vc<vi> g(n);
  vi deg(n);
  vc<vi> t(m);
  rep(i, n) {
    int k;
    cin >> k;
    while (k--) {
      int x;
      cin >> x;
      --x;
      t[x].pb(i);
      lst[x] = i;
    }
  }
  rep(i, m) {
    int w = lst[i];
    for (auto j : t[i]) {
      if (j == w)
        continue;
      g[j].pb(w);
      deg[w] += 1;
    }
  }
  pq<int> q;
  rep(i, n) if (deg[i] == 0) q.emplace(i);
  vi order;
  while (!q.empty()) {
    int u = q.top();
    q.pop();
    order.pb(u);
    for (auto v : g[u])
      if (--deg[v] == 0) {
        q.emplace(v);
      }
  }
  // debug(order);
  if (is_sorted(all(order))) {
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
  for (auto i : order) {
    cout << i + 1 << " ";
  }
  cout << "\n";
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