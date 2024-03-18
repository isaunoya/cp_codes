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

void solve() {
  vi a(3);
  rep(i, 3) cin >> a[i];
  rep(i, 3) {
    int x = a[i];
    int j = 0;
    while (i == j)
      j++;
    int k = j + 1;
    while (i == k)
      k++;
    int y = a[j];
    int z = a[k];
    // debug(i, j, k);
    if (y > z)
      swap(y, z);
    // y <= z
    int dt = z - y;
    if (dt % 2 == 0) {
      x += y;
      z -= y;
      y = 0;
      int ans = 1;
      while (y < z) {
        if (x == 0) {
          ans = 0;
          break;
        }
        while (x && z)
          x--, z--, y++;
        while (y && z)
          y--, z--, x++;
      }
      cout << ans << " ";
    } else {
      cout << 0 << " ";
    }
  }
  cout << "\n";
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