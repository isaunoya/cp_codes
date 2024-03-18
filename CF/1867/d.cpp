#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
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

template <class... T> void read() {}
template <class T> void read(T &x) { cin >> x; }
template <class T, class S> void read(pair<T, S> &v) {
  read(v.first, v.second);
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

void solve() {
  int n, k;
  cin >> n >> k;
  vi a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    --a[i];
  }
  if (k == 1) {
    vi p(n);
    iota(all(p), 0);
    if (a == p) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
    return;
  }
  vi deg(n);
  for (int i = 0; i < n; i++) {
    deg[a[i]] += 1;
  }
  vi dep(n, -1);
  bool ok = true;
  int o = k;
  vi vis(n, -1);
  auto dfs = [&](auto &self, int u) -> void {
    int v = a[u];
    if (vis[v] != -1) {
      o = vis[v];
      return;
    }
    {
      if (dep[v] == -1) {
        dep[v] = dep[u] + 1;
        self(self, v);
      } else {
        // debug(u, v);
        o = dep[u] + 1 - dep[v];
        int t = v;
        while (t != u) {
          // debug(t);
          vis[t] = o;
          t = a[t];
        }
        vis[t] = o;
        return;
      }
    }
  };


  for (int i = 0; i < n; i++) {
    if (deg[i] == 0) {
      dep[i] = 0;
      dfs(dfs, i);
      ok &= (o == k);
    }
  }
  for (int i = 0; i < n; i++) {
    if (dep[i] == -1) {
      dep[i] = 0;
      dfs(dfs, i);
      ok &= (o == k);
    }
  }

  if (ok) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
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