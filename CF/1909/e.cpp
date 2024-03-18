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

vector<int> all[20];

void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> g(n + 1);
  rep(i, m) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
  }
  if (n >= 20) {
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
      cout << i << " \n"[i == n];
    }
    return;
  }

  vi must_done(n + 1);
  for (int i = 1; i <= n; i++) {
    must_done[i] = 0;
    for (int j : g[i]) {
      must_done[i] |= 1 << j - 1;
    }
  }

  for (auto s : all[n]) {
    int t = s;
    rep(i, n) if (s >> i & 1) { t |= must_done[i + 1]; }
    if (s == t) {
      int cnt = __builtin_popcount(s);
      cout << cnt << "\n";
      rep(i, n) {
        if (s >> i & 1) {
          cout << i + 1 << " ";
        }
      }
      cout << "\n";
      return;
    }
  }
  cout << -1 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int n = 5; n <= 19; n++) {
    vi light(n + 1);
    vi ans;
    rep(s, 1, 1 << n) {
      ans.clear();
      for (int i = 0; i <= n; i++)
        light[i] = 0;
      rep(i, n) {
        if (s >> i & 1) {
          ans.pb(i + 1);
        }
      }
      for (int x : ans) {
        for (int y = x; y <= n; y += x) {
          light[y] ^= 1;
        }
      }
      if (count(all(light), 1) <= n / 5) {
        all[n].pb(s);
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