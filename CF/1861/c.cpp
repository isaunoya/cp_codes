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
  string s;
  cin >> s;
  int n = sz(s);
  vi a;
  int c = 1;
  bool ok = true;
  vi t(n + 1);
  int neg = 0;
  int mx = 0;
  rp(i, n) {
    if (s[i] == '+') {
      a.pb(c);
      c += 1;
    }
    if (s[i] == '-') {
      if (a.back() < 0)
        neg--;
      a.pop_back();
    }
    if (s[i] == '1') {
      if (neg > 0) {
        ok = false;
        break;
      }
      if (sz(a))
        cmax(mx, a.back());
    }
    if (s[i] == '0') {
      if (a.size() <= 1) {
        ok = false;
        break;
      }
      if (a.back() > 0 && a.back() <= mx) {
        ok = false;
        break;
      }
      if (a.back() > 0)
        a.back() = -a.back(), neg++;
    }
  }
  if (ok) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
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