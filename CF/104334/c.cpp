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

const int N = 2000;
int a[N][N];
// sol1: (i, 0) a[i][0...i]^=1
// sol2: (i, i) a[i...n-1][i]^=1
// sol3: (i, 1) a[i][1..i-1]^=1, a[i+1][2...i-2]^=1,
void solve() {
  int n;
  cin >> n;
  rep(i, n) rep(j, i + 1) {
    char c;
    cin >> c;
    a[i][j] = c & 1;
  }
  debug("ok");
  vi b(n);
  vc<vi> c(n, vi(n * 2 + 1));
  rep(i, n) {
    int cur = 0;
    rep(j, 1, n) c[i][j] ^= c[i][j - 1];
    debug(c[i]);
    rep(j, i + 1) {
      int now = a[i][j] ^ cur ^ b[j] ^ c[i][j];
      if (now) {
        debug(i, j);
        if (j == 0) {
          cur ^= 1;
        } else if (j == i) {
          b[j] ^= 1;
        } else if (j == 1) {
          // debug(i,j);
          int l = 1, r = i - 1;
          // debug(l,r);
          rep(k, l, r + 1) a[i][k] ^= 1;
          int p = n;
          rep(k, i + 1, n) {
            l += 1;
            debug(k, l, r);
            if (l <= r) {
              c[k][l] ^= 1;
              c[k][r + 1] ^= 1;
            } else {
              p = k + 1;
              break;
            }
          }
          rep(k, p, n) {
            r += 1;
            debug(k, l, r);
            c[k][l] ^= 1;
            c[k][r + 1] ^= 1;
          }
        } else {
          cout << "No\n";
          return;
        }
      }
    }
  }
  cout << "Yes\n";
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