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

int id[7][11];
int nxt[20][20];
int a[20];
ll dp[1 << 19];
vector<array<int, 3>> e;

ll f(int s) {
  if (dp[s] != -1) {
    return dp[s];
  }
  ll ans = 0;
  rep(i, 19) {
    if (s >> i & 1) {
      cmax(ans, f(s ^ (1 << i)));
    }
  }
  for (auto [x, y, z] : e) {
    if ((s >> x & 1) && (s >> y & 1)) {
      int ns = s ^ (1 << x) ^ (1 << y);
      ns |= 1 << z;
      cmax(ans, f(ns) + a[y]);
    } 
  }
  return dp[s] = ans;
}

void solve() {
  int s = 0;
  rep(i, 19) {
    char c;
    cin >> c;
    if (c == '#') {
      s |= 1 << i;
    }
  }
  cout << f(s) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(id, -1, sizeof id);
  memset(nxt, -1, sizeof nxt);
  memset(dp, -1, sizeof dp);
  id[1][3] = 0, id[1][5] = 1, id[1][7] = 2;
  id[2][2] = 3, id[2][4] = 4, id[2][6] = 5, id[2][8] = 6;
  id[3][1] = 7, id[3][3] = 8, id[3][5] = 9, id[3][7] = 10, id[3][9] = 11;
  id[4][2] = 12, id[4][4] = 13, id[4][6] = 14, id[4][8] = 15;
  id[5][3] = 16, id[5][5] = 17, id[5][7] = 18;

  for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= 10; j++) {
      if (id[i][j] == -1) {
        continue;
      }
      int x = id[i][j];
      for (int k = -1; k <= 1; k++) {
        for (int l = -2; l <= 2; l++) {
          if (abs(k) + abs(l) == 2) {
            int ii = i + k;
            int jj = j + l;
            if (id[ii][jj] == -1) {
              continue;
            }
            int y = id[ii][jj];
            nxt[x][y] = id[ii + k][jj + l];
          }
        }
      }
    }
  }
  rep(i, 19) rep(j, 19) if (nxt[i][j] != -1) {
    e.push_back(array<int, 3>{i, j, nxt[i][j]});
  }
  debug(e.size());

  rep(i, 19) cin >> a[i];

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}