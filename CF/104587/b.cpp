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

bool f[10][10][101][101][9];
vector<pair<int, int>> d;

void solve() {
  int r, c;
  cin >> r >> c;
  vc<vc<char>> a(r, vc<char>(c));
  rep(i, r) rep(j, c) cin >> a[i][j];
  int k;
  cin >> k;
  string s;
  cin >> s;
  int n = sz(s);
  if (k >= n) {
    cout << "NO\n";
    return;
  }
  rep(i, r) rep(j, c) {
    if (a[i][j] != s[0])
      continue;
    if (n == 1) {
      if (k == 0) {
        cout << "YES\n";
        return;
      } else {
        cout << "NO\n";
        return;
      }
    }
    queue<array<int, 5>> q;
    q.emplace(array<int, 5>{i, j, 1, -1, -1});
    while (!q.empty()) {
      auto [x, y, now, cnt, lst] = q.front();
      q.pop();
      if (f[x][y][now][cnt + 1][lst + 1]) {
        continue;
      }
      f[x][y][now][cnt + 1][lst + 1] = 1;
      debug(x, y, now, cnt, lst);
      if (now == n && cnt == k) {
        cout << "YES\n";
        return;
      }
      if (cnt > k) {
        continue;
      }
      for (int p = 0; p < d.size(); p++) {
        auto [dx, dy] = d[p];
        int nx = x + dx;
        int ny = y + dy;
        // debug(nx,ny);
        // debug(r,c);
        if (nx < 0 || nx >= r)
          continue;
        if (ny < 0 || ny >= c)
          continue;
        // debug(nx,ny);
        if (a[nx][ny] == s[now]) {
          q.emplace(array<int, 5>{nx, ny, now + 1, cnt + (lst != p), p});
        }
      }
    }
  }
  cout << "NO\n";
}

int main() {
  debug(sizeof(f) / 1048576.);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // debug(d);
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      if (i || j)
        d.pb(i, j);
  // debug(d);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}