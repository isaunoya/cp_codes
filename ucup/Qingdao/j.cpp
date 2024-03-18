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
  ll a, b, c, d, v, t;
  cin >> a >> b >> c >> d >> v >> t;
  vc<ll> V;
  ll l = lcm(a, c);
  V.pb(0);
  for (ll i = a; i < l; i += a)
    V.pb(i);
  for (ll i = c; i <= l; i += c)
    V.pb(i);
  sort(all(V));
  ll tmp = 0;
  for (int i = 1; i < V.size(); i++) {
    if (V[i] - V[i - 1] > v) {
      tmp += 1;
    }
  }
  ll ans = (t / a) * b + (t / c) * d + b + d - 1;
  ll cur = t / l;
  ans = ans - cur * tmp;
  t %= l;
  for (int i = 1; V[i] <= t; i++) {
    if (V[i] - V[i - 1] > v) {
      ans -= 1;
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