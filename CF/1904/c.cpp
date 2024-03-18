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
  int n, k;
  cin >> n >> k;
  vc<ll> a(n);
  rep(i, n) cin >> a[i];
  if (k == 1) {
    ll ans = *min_element(all(a));
    rep(i, n) rep(j, i + 1, n) cmin(ans, abs(a[i] - a[j]));
    cout << ans << "\n";
    return;
  } else if (k == 2) {
    ll ans = *min_element(all(a));
    vc<ll> cur;
    rep(i, n) rep(j, i + 1, n) cmin(ans, abs(a[i] - a[j])), cur.pb(abs(a[i] - a[j]));
    sort(all(cur));
    sort(all(a));
    // debug(a);
    int j = 0;
    rep(i, cur.size()) {
      while (j < n && a[j] < cur[i]) j += 1;
      if (j + 1 != n) cmin(ans, a[j] - cur[i]);
      if (j > 0) cmin(ans, cur[i] - a[j - 1]);
    }

    cout << ans << "\n";
  } else {
    cout << 0 << "\n";
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