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
  int n, w, k;
  cin >> n >> w >> k;
  vc<pii> t(n);
  for (auto &[wi, vi] : t) cin >> wi >> vi;

  sort(all(t), [&](auto x, auto y) {
    return x.first < y.first;
  });

  vi vals;
  vc<ll> values(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    auto [wi, vi] = t[i];
    vals.insert(lower_bound(all(vals), vi), vi);
    ll res = 0;
    int s = sz(vals);
    for (int j = s - 1; j >= max(0, s - k); j--) res += vals[j];
    values[i] = res;
  }
  vc<ll> dp(w + 1);
  ll ans = values[0];
  for (int i = 0; i < n; i++) {
    auto [wi, vi] = t[i];
    for (int j = w; j >= wi; j--) cmax(dp[j], dp[j - wi] + vi);
    cmax(ans, dp[w] + values[i + 1]);
  }

  cout << ans << "\n";
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