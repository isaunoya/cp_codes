#include <algorithm>
#include <bits/stdc++.h>

#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> g(n);
  rp(i, m) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    g[b].pb(a);
  }
  queue<int> q;
  q.emplace(0);
  vi d(n, -1);
  d[0] = 0;
  while (sz(q)) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (d[v] == -1) {
        d[v] = d[u] + 1;
        q.emplace(v);
      }
    }
  }
  if (*min_element(all(d)) == -1) {
    cout << "INFINITE\n";
  } else {
    cout << "FINITE\n";
    vc<vi> gp(n);
    rp(i, n) gp[d[i]].pb(i);
    vi ans;
    for (int i = n - 1; i >= 0; i--) {
      rep(j, i, n) for (auto v : gp[j]) { ans.pb(v); }
    }
    cout << sz(ans) << "\n";
    for (int x : ans)
      cout << x + 1 << " ";
    cout << "\n";
  }
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