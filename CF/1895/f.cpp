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

const int P = 1e9 + 7;
vector<vector<int>> operator* (vector<vector<int>> a, const vector<vector<int>> &b) {
 int N, M, K;
 N = (int) a.size();
 K = min((int) a[0].size(), (int) b.size());
 M = (int) b[0].size();
 vector<vector<int>> c(N, vector<int>(M, 0));
 rep (i, 0, N) {
  rep (k, 0, K) {
   rep (j, 0, M) {
    c[i][j] += (long long) a[i][k] * b[k][j] % P;
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
   res = (long long) res * x % P;
  }
  x = (long long) x * x % P;
  y /= 2;
 }
 return res;
}

vector<vector<int>> power(vector<vector<int>> x, int y) {
  int n = x.size();
  vector<vector<int>> res(n, vi(n));
  rep(i, n) res[i][i] = 1;
  // debug(res);
  while (y) {
    if (y % 2 == 1) {
      res = res * x;
    }
    x = x * x;
    y /= 2;
  }

  return res;
}
int inverse(int x) {
 return power(x, P - 2);
}

void solve() {
  int n, x, k;
  cin >> n >> x >> k;
  int ans = 1ll * (x + k) * power(2 * k + 1, n - 1) % P;
  if (x == 0) {
    cout << ans << "\n";
    return;
  }
  vector<vector<int>> base(x, vi(x));
  rep(i, x) {
    rep(j, x) {
      if (abs(i - j) <= k) {
        base[i][j] = 1;
      }
    }
  }

  // debug(base);
  auto mat = power(base, n - 1);

  rep(i, x) {
    rep(j, x) {
      ans += P - mat[i][j];
      if (ans >= P) {
        ans -= P;
      }
    }
  }

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