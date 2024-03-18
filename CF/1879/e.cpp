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
  int n;
  cin >> n;
  vi p(n, -1);
  rep(i, 1, n) cin >> p[i], --p[i];
  vi dep(n, 0), deg(n, 0);
  rep(i, 1, n) {
    dep[i] = dep[p[i]] + 1;
    deg[p[i]] += 1;
  }
  int k;
  vi col(n);
  if (*max_element(all(dep)) == 1) {
    k = 1;
  } else {
    vc<vi> adj(n);
    rep(i, 1, n) { adj[p[i]].pb(i); }
    bool ok = true;
    rep(i, n) {
      if (p[i] == 0) {
        int cnt[2]{};
        auto dfs = [&](auto self, int u) -> void {
          if (deg[u] == 1) {
            cnt[dep[u] % 2] += 1;
          }
          for (auto v : adj[u]) {
            col[v] = !col[u];
            self(self, v);
          }
        };
        dfs(dfs, i);
        if (cnt[0] && cnt[1]) {
          ok = false;
          break;
        } else {
          col[i] = cnt[0] ? 1 : 0;
          dfs(dfs, i);
        }
      }
    }
    if (ok) {
      k = 2;
    } else {
      k = 3;
      for (int i = 1; i < n; i++) {
        col[i] = dep[i] % 3;
      }
    }
  }

  cout << k << "\n";
  rep(i, 1, n) { cout << col[i] + 1 << " \n"[i + 1 == n]; }

  cout.flush();

  while (true) {
    int x;
    cin >> x;
    if (x == 1) {
      break;
    }
    vi u;
    rep(i, k) {
      int c;
      cin >> c;
      if (c == 1) {
        u.pb(i);
      }
    }
    if (sz(u) > 1) {
      if (k == 2) {
        u[0] = 0;
      } else {
        if ((u[0] + 1) % 3 != u[1]) {
          swap(u[0], u[1]);
        }
      }
    }
    cout << u[0] + 1 << endl;
  }
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