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
  int N;
  ll K;
  cin >> N >> K;
  vector<pair<int, int>> pairs(N);
  ll X = 0, Y = 0;
  for (int i = 0; i < N; i++) {
    cin >> pairs[i].first >> pairs[i].second;
    if (pairs[i].first < pairs[i].second) {
      X += pairs[i].first;
    } else {
      Y += pairs[i].second;
    }
  }
  vector<ll> dp(X + 1, -lnf);       // use i volume can get dp[i] values
  vector<ll> dp2(Y + 1, lnf); // get i values need dp2[i] at least
  dp[0] = 0;
  dp2[0] = 0;
  for (auto [x, y] : pairs) {
    if (x < y) {
      for (int i = X; i >= x; i--) {
        cmax(dp[i], dp[i - x] + y);
      }
    } else {
      for (int i = Y; i >= y; i--) {
        cmin(dp2[i], dp2[i - y] + x);
      }
    }
  }
  ll ans = 0;
  for (int i = 0; i <= min(K, X); i++) {
    int rem = K - i;
    int t = --upper_bound(all(dp2), rem) - begin(dp2);
    cmax(ans, dp[i] + t);
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