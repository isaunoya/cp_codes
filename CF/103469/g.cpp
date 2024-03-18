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

ll two(int x) { return 1ll * x * (x - 1) / 2; }

const int N = 2048;
bitset<N> b[N], y[N];
void solve() {
  int n;
  cin >> n;
  rep(i, n) {
    rep(j, n) {
      char c;
      cin >> c;
      
      if (i == j)
        continue;
      if (c == 'B') {
        b[i][j] = 1;
      } else {
        y[i][j] = 1;
      }
    }
  }
  array<ll, 2> ans;
  ans[0] = ans[1] = 0;
  rep(i, n) {
    rep(j, i + 1, n) {
      if (b[i][j]) {
        int c = (y[i] & y[j]).count();
        ans[0] += two(c);
      } else {
        int c = (b[i] & b[j]).count();
        ans[0] += two(c);
      }
      ans[1] += 1ll * (b[i] & y[j]).count() * (b[j] & y[i]).count();
    }
  }
  ans[1] /= 2;
  cout << ans[1] - ans[0] << "\n";
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