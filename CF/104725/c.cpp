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
const int P = 998244353;
vector<vector<int>> operator*(vector<vector<int>> a,
                              const vector<vector<int>> &b) {
  int N, M, K;
  N = (int)a.size();
  K = min((int)a[0].size(), (int)b.size());
  M = (int)b[0].size();
  vector<vector<int>> c(N, vector<int>(M, 0));
  rep(i, 0, N) {
    rep(k, 0, K) {
      rep(j, 0, M) {
        c[i][j] += (long long)a[i][k] * b[k][j] % P;
        if (c[i][j] >= P) {
          c[i][j] -= P;
        }
      }
    }
  }
  return c;
}
int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) {
      res = (long long)res * x % P;
    }
    x = (long long)x * x % P;
    y /= 2;
  }
  return res;
}
int inverse(int x) { return power(x, P - 2); }
int val(vector<vector<int>> &a) {
  int N = (int)a.size();
  bool rev = false;
  int res = 1;
  rep(i, 0, N) {
    if (!a[i][i]) {
      rep(j, i + 1, N) {
        if (a[j][i]) {
          swap(a[i], a[j]);
          rev ^= 1;
          break;
        }
      }
    }
    rep(j, i + 1, N) {
      int d = (long long)a[j][i] * inverse(a[i][i]) % P;
      rep(k, i + 1, N) {
        a[j][k] -= (long long)d * a[i][k] % P;
        a[j][k] += a[j][k] >> 31 & P;
      }
      a[j][i] = 0;
    }
    if (!a[i][i]) {
      return 0;
    }
    res = (long long)res * a[i][i] % P;
  }
  if (rev) {
    return P - res;
  } else {
    return res;
  }
}

void md(int &x) {
  if (x >= P) {
    x -= P;
  }
}
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vc<vi> a(n, vi(n));
  vi deg(n);
  rep(i, m) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    a[x][y] = 1;
    deg[y]++;
  }
  vc<vi> x(n - 1, vi(n - 1));
  vc<vi> y(n, vi(n)), z(n, vi(n));
  rep(i, n) rep(j, n) {
    if (i == j) {
      int dd = 1ll * n * k % P - deg[i] - 1;
      md(y[i][j] = dd + P);
    } else {
      int v = a[i][j];
      y[i][j] = v;
      md(y[i][j] += P - 1);
    }
  }
  if (k == 1) {
    rep(i, n - 1) rep(j, n - 1) x[i][j] = y[i + 1][j + 1];
    cout << val(x) << "\n";
    return;
  }
  rep(i, n - 1) rep(j, n - 1) md(x[i][j] = y[i + 1][j + 1] + P - y[0][j + 1]);
  rep(i, n) rep(j, n) if (i == n - 1) z[i][j] = 1;
  else z[i][j] = y[i][j];
  rep(i, n) rep(j, n) md(y[i][j] += 1);
  debug(x, y, z);
  debug(val(x), val(y), val(z));
  cout << 1ll * val(x) * power(val(y), k - 2) % P * val(z) % P << "\n";
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