#include <bits/stdc++.h>

#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

void solve() {
  int n;
  cin >> n;
  vi a(n);
  rp(i, n) cin >> a[i];
  int asd = 0;
  rep(i, 1, n) if (a[i - 1] >= a[i])++ asd;
  int ans = asd;
  int dec = 0;
  for (int i = 1; i < n; i++) { // [0,i), [i,n)
    if (a[i - 1] >= a[i])
      --asd;
    cmin(ans, dec + asd + 1);
    if (a[i - 1] <= a[i])
      ++dec;
  }
  cmin(ans, dec + 1);
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