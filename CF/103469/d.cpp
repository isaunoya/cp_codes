#pragma GCC optimize("Ofast")
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

const int N = 4005;
ll dp[N][N], a[N][N];
bitset<N> ok[N], ok2[N];
pii b[N * N / 4];
bool t[N][N];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j += 2) {
      cin >> a[i][j];
      b[a[i][j]] = make_pair(i, j + 1);
    }
  }
  for (int i = 1; i <= n + 1; i++) {
    ok[i][i] = ok2[i][i] = 1;
  }
  for (int val = 1; val <= n * n / 4; val++) {
    auto [i, j] = b[val];
    t[i][j] = 1;
    if (ok[i][j]) {
      continue;
    }
    if (ok[i + 1][j - 1]) {
      ok[i][j] = ok2[j][i] = 1;
    }
    if (!ok[i][j]) {
      continue;
    }
    queue<pii> q;
    q.emplace(i, j);
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      if (!ok[x - 1][y + 1] && x > 0 && t[x - 1][y + 1]) {
        ok[x - 1][y + 1] = ok2[y + 1][x - 1] = 1;
        q.emplace(x - 1, y + 1);
      }
      if (!ok[x - 2][y] && x > 1 && t[x - 2][x]) {
        ok[x - 2][y] = ok2[y][x - 2] = 1;
        q.emplace(x - 2, y);
      }
      if (!ok[x][y + 2] && y + 1 <= n && t[y][y + 2]) {
        ok[x][y + 2] = ok2[y + 2][x] = 1;
        q.emplace(x, y + 2);
      }
      auto tmp = (ok[y] & (~ok[x]));
      for (auto t = tmp._Find_first(); t <= n + 1; t = tmp._Find_next(t)) {
        ok[x][t] = ok2[t][x] = 1;
        q.emplace(x, t);
      }
      tmp = (ok2[x] & (~ok2[y]));
      for (auto t = tmp._Find_first(); t <= n + 1; t = tmp._Find_next(t)) {
        ok[t][y] = ok2[y][t] = 1;
        q.emplace(t, y);
      }
    }
    if (ok[1][n + 1]) {
      cout << val << "\n";
      return;
    }
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