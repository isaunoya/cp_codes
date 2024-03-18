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

int dp[256][256];
vector<tuple<int, int, int>> tuples;
void solve() {
  int a, b, c, d, m;
  cin >> a >> b >> c >> d >> m;
  array<int, 8> X;
  rep(i, 8) X[i] = 0;
  rep(i, 30) {
    int e = 0;
    if (a >> i & 1) {
      e += 1;
    }
    if (b >> i & 1) {
      e += 2;
    }
    if (m >> i & 1) {
      e += 4;
    }
    X[e] ^= 1 << i;
  }

  int ans = inf;
  for (auto [x, y, dist] : tuples) {
    int xx = 0, yy = 0;
    rep(i, 8) xx |= (x >> i & 1) * X[i];
    rep(i, 8) yy |= (y >> i & 1) * X[i];
    if (xx == c && yy == d) {
      cmin(ans, dist);
    }
  }
  if (ans == inf) ans = -1;
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(dp, 0x3f, sizeof dp);
  {
    int a = 0, b = 0, m = 0;
    rep(i, 0, 2) {
      rep(j, 0, 2) {
        rep(k, 0, 2) {
          int v = i + j * 2 + k * 4;
          if (i) {
            a |= 1 << v;
          }
          if (j) {
            b |= 1 << v;
          }
          if (k) {
            m |= 1 << v;
          }
        }
      }
    }
    dp[a][b] = 0;
    queue<pair<int, int>> q;
    q.emplace(a, b);
    auto add = [&](int x, int y, int d) {
      if (dp[x][y] > d) {
        dp[x][y] = d;
        q.emplace(x, y);
      }
    };
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      int d = dp[x][y];
      add(x & y, y, d + 1);
      add(x | y, y, d + 1);
      add(x, x ^ y, d + 1);
      add(x, y ^ m, d + 1);
    }
  }
  rep(x, 256) rep(y, 256) if (dp[x][y] != 0x3f3f3f3f) {
    tuples.emplace_back(x, y, dp[x][y]);
  }
  debug(tuples.size());
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}