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

void solve() {
  int n, k;
  cin >> n >> k;
  vc<vi> g(n);
  vi Deg(n);
  vi q;
  rep(t, k) {
    vi a(n);
    rep(i, n) cin >> a[i], --a[i];
    rep(i, 2, n) {
      int x = a[i - 1];
      int y = a[i];
      g[x].pb(y);
      Deg[y] += 1;
    }
    q.pb(a[0]);
    q.pb(a[1]);
  }

  if (k == 1) {
    cout << "YES\n";
    return;
  }

  vi d(n), deg(n);

  {
    queue<int> q;
    rep(i, n) d[i] = 0, deg[i] = Deg[i];
    rep(i, n) if (deg[i] == 0) {
      q.emplace(i);
    } 
     while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto v : g[u]) {
        cmax(d[v], d[u] + 1);
        if (--deg[v] == 0) {
          q.emplace(v);
        }
      }
    }

    rep(i, n) if (deg[i]) {
      cout << "NO\n";
      return;
    }
  }
  auto bfs = [&](int s) {
    rep(i, n) d[i] = 0, deg[i] = Deg[i]; 
    d[s] = 0;
    queue<int> q;
    q.emplace(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto v : g[u]) {
        cmax(d[v], d[u] + 1);
        if (--deg[v] == 0) {
          q.emplace(v);
        }
      }
    }
    return *max_element(all(d));
  };

  sort(all(q));
  q.resize(unique(all(q)) - q.begin());

  for (auto i : q) {
    if (bfs(i) > n) {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
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