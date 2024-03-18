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

int get(char c) {
  if ('a' <= c && c <= 'z') {
    return c - 'a';
  } else {
    return c - 'A' + 26;
  }
}

void solve() {
  string a, b;
  cin >> a >> b;
  int n = sz(a);

  vi c(52);
  int kind = 0;
  rep(i, n) {
    int bb = get(b[i]);
    ++c[bb];
    if (c[bb] == 1) {
      kind += 1;
    }
  }

  if (kind == 52) {
    if (a == b) {
      cout << 0 << "\n";
    } else {
      cout << -1 << "\n";
    }
    return;
  }

  vi to(52, -1);

  rep(i, n) {
    int aa = get(a[i]), bb = get(b[i]);
    if (to[aa] == -1) {
      to[aa] = bb;
    } else if (to[aa] != bb) {
      cout << -1 << "\n";
      return;
    }
  }
  rep(i, 52) {
    if (to[i] == i) {
      to[i] = -1;
    }
  }

  // debug(to);
  int ans = 0;
  vi deg(52);
  rep(i, 52) {
    if (to[i] != -1) {
      // debug(i, to[i]);
      ans += 1;
      deg[to[i]] += 1;
    }
  }
  // debug(ans);

  queue<int> q;
  vi vis(52);
  rep(i, 52) if (deg[i] == 0) q.emplace(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 1;
    int v = to[u];
    if (v == -1) {
      continue;
    }
    if (!vis[v]) {
      deg[v] = 0;
      q.emplace(v);
    }
  }

  auto dfs = [&](auto &dfs, int u) -> void {
    if (u == -1) {
      return;
    }
    if (vis[u]) {
      return;
    }
    vis[u] = 1;
    int v = to[u];
    dfs(dfs, v);
  };
  rep(i, 52) if (!vis[i]) dfs(dfs, i), ans += 1;

  cout << ans << "\n";
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