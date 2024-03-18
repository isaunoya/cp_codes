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
  int n;
  cin >> n;
  string str;
  cin >> str;
  vi s(n);
  rep(i, n) s[i] = str[i] - '0';

  vi a(n);
  rep(i, n) cin >> a[i], --a[i];

  vc<vc<pii>> g(n);
  rep(i, n) {
    int x = i, y = a[i];
    // debug(x, y);
    g[x].pb(y, i);
    g[y].pb(x, i);
  }
  vi vis(n);
  int ic = -1;
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    vis[u] = 1;
    for (auto [v, id] : g[u]) {
      if (v == p) {
        continue;
      } else {
        if (vis[v]) {
          ic = id;
        } else {
          dfs(dfs, v, u);
        }
      }
    }
  };

  int k = 0;
  vi res[2];
  vi dep(n);
  vi w(n);
  auto dfs2 = [&](auto &dfs2, int u, int p) -> void {
    w[u] = s[u];
    for (auto [v, id] : g[u]) {
      if (v == p) {
        continue;
      } else if (id == ic)
        continue;
      dep[v] = dep[u] + 1;
      dfs2(dfs2, v, u);
      if (w[v]) {
        res[k].pb(id);
        w[v] ^= 1, w[u] ^= 1;
      }
    }
  };

  vi ans;
  rep(i, n) if (!vis[i]) {
    k = 0;
    ic = -1;
    dfs(dfs, i, -1);
    bool ok1 = false, ok2 = false;
    res[0].clear();
    dep[i] = 0;
    dfs2(dfs2, i, -1);
    if (w[i] % 2 == 0) {
      ok1 = true;
    }
    k++;
    res[1].clear();
    dep[i] = 0;
    res[1].pb(ic);
    s[a[ic]] ^= 1, s[ic] ^= 1;
    dfs2(dfs2, i, -1);
    if (w[i] % 2 == 0) {
      ok2 = true;
    }
    if (ok1 && ok2) {
      if (res[0].size() < res[1].size()) {
        ans.insert(ans.end(), all(res[0]));
      } else {
        ans.insert(ans.end(), all(res[1]));
      }
    } else if (ok1) {
      ans.insert(ans.end(), all(res[0]));
    } else if (ok2) {
      ans.insert(ans.end(), all(res[1]));
    } else {
      cout << "-1\n";
      return;
    }
  }

  cout << sz(ans) << "\n";
  for (int i : ans) {
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