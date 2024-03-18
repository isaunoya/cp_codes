#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (auto i = 0; i < a; i++)
#define rep2(i, a) for (auto i = 0; i < a; i++)
#define rep3(i, a, b) for (auto i = a; i < b; i++)
#define rep4(i, a, b, c) for (auto i = a; i < b; i += c)
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
  int n, m;
  cin >> n >> m;
  vc<pii> a(n);
  rep(i, n) cin >> a[i].first >> a[i].second;
  if (n == 1) {
    cout << a[0].second << "\n";
    return;
  }
  ll res = 0;
  if (2 * n - 1 <= m) {
    ll ans = 0;
    rep(i, n) ans += a[i].second;
    cmax(res, ans);
  }
  int interval = m - n;
  int t = min(interval, n - 1);
  ll ans = 0;
  rep(i, n) ans += a[i].first;
  cmax(res, ans);
  sort(all(a),
       [&](auto x, auto y) { return x.second - x.first > y.second - y.first; });
  int rem = n;
  int i = 0;
  while (t--) {
    if (a[i].second > a[i].first) {
      ans += a[i].second - a[i].first;
      rem -= 1;
    }
    i++;
    if (rem >= 2) {
      cmax(res, ans);
    } else {
      break;
    }
  }
  cout << res << "\n";
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