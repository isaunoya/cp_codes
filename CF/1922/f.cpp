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

int N, X;
int f[105][105][105][2], MN[105][105][105], SMN[105][105][105];
// f[l][r][x][0], min cost of [l,r]=x
// f[l][r][x][1], min cost of [l,r] don't have x

int dfs(int l, int r, int v, int p) {
  if (~f[l][r][v][p])
    return f[l][r][v][p];
  int &res = f[l][r][v][p] = N;
  rep(m, l, r) cmin(res, dfs(l, m, v, p) + dfs(m + 1, r, v, p));
  cmin(res, dfs(l, r, v, p ^ 1) + 1);
  if (p == 1) {
    int &mn = MN[l][r][v], &smn = SMN[l][r][v];
    if (mn == -1 && smn == -1) {
      mn = smn = N;
      rep(x, X) {
        int val = dfs(l, r, x, 0);
        if (val < mn) {
          smn = mn, mn = val;
        } else if (val < smn) {
          smn = val;
        }
      }
    }
    cmin(res, dfs(l, r, v, 0) == mn ? smn : mn);
  }
  return res;
}

void solve() {
  cin >> N >> X;
  rep(i, N) rep(j, N) rep(k, X) {
    rep(l, 2) f[i][j][k][l] = -1;
    MN[i][j][k] = SMN[i][j][k] = -1;
  }
  rep(i, N) {
    int x;
    cin >> x;
    --x;
    rep(j, X) {
      f[i][i][j][0] = (j != x);
      f[i][i][j][1] = (j == x);
    }
  }
  int ans = N;
  rep(i, X) cmin(ans, dfs(0, N - 1, i, 0));
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