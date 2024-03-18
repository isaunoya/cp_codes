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
  ll n, m, a, b;
  cin >> n >> m >> a >> b;
  vc<vi> g(n);
  rep(i, m) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }

  vc<ll> l(n);
  rep(i, n) cin >> l[i];
  rep(i, 1, n) l[i] += b;
  if (a <= b) {
    queue<int> q;
    q.emplace(0);
    vc<ll> w(n);
    vc<ll> d(n, -1);
    w[0] = l[0];
    d[0] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : g[u]) {
        if (d[v] == -1 && w[u] > l[v])
          d[v] = d[u] + 1, w[v] = w[u] + a - b, q.emplace(v);
      }
    }
    cout << d.back() << "\n";
  } else {
    pqg<pair<ll, ll>> q;
    vi vis(n);
    auto add = [&](int u) {
      vis[u] = 1;
      for (auto v : g[u]) {
        if (!vis[v]) {
          q.emplace(l[v], v);
        }
      }
    };
    add(0);
    ll pw = l[0];
    vi list;
    while (!q.empty()) {
      auto [val, v] = q.top();
      q.pop();
      if (val < pw) {
        pw += a - b;
        add(v);
        list.pb(v);
      } else {
        break;
      }
    }
    if (!vis.back()) {
      cout << "-1\n";
      return;
    }
    while (!q.empty()) q.pop();
    
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
