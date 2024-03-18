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

int power(int x, int y, const int &p) {
  int res = 1;
  while (y) {
    if (y % 2 == 1) {
      res = 1ll * res * x % p;
    }
    y /= 2;
    x = 1ll * x * x % p;
  }
  return res;
}

void solve() {
  int p, q;
  cin >> p >> q;
  while (q--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if ((a + b) % p != (c + d) % p) {
      cout << -1 << "\n";
      continue;
    }
    ll bin = 1;
    int l = (a + b) % p;
    int inv = power(l, p - 2, p);
    for (int ans = 0;; ans++) {
      int r = (c + bin * b) % p;
      int x = 1ll * r * inv % p;
      if (x == 0) {
        x = p;
      }
      // debug(l, x, r);
      if (x <= bin) {
        cout << ans << "\n";
        break;
      }
      bin = 2 * bin;
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