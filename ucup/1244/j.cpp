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
  ll X, Y, K;
  cin >> X >> Y >> K;

  if (K <= 1) {
    cout << abs(Y - X) << "\n";
    return;
  }

  if (X > Y) swap(X, Y);

  K += 1;
  ll K2 = 1;
  while (K2 < K) {
    K2 = K2 * 2;
  }
  K -= 1;
  K2 -= 1;

  // debug(K, K2);

  ll o = Y - X;
  ll coef = 2LL + (K < K2);
  ll ans = 0;
  for (int i = 60; i >= 0; i--) {
    ll base = 1LL << i;
    if (K2 & base) {
      break;
    }

    if ((Y & base) == base && ((X & base) == 0LL)) {
      ll rem = Y & K2;
      if (rem == 0) {

      } else if (rem <= K) {
        Y -= rem;
        ans += 1;
      } else {
        Y -= rem;
        ans += 2;
      }
      rem = (Y - base) / (K2 + 1);
      ans += rem * coef;
      Y = base - 1;
      ans += 1;
    } else if (((Y & base) == 0LL && ((X & base) == base))) {
      ll rem = X & K2;
      if (rem == 0) {

      } else if (rem <= K) {
        X -= rem;
        ans += 1;
      } else {
        X -= rem;
        ans += 2; 
      }
      rem = (X - base) / (K2 + 1);
      ans += rem * coef;
      X = base - 1;
      ans += 1;
    } else {
      Y &= ~base;
      X &= ~base;
    }
  }

  ll res = 2;
  for (int i = -2; i <= 2; i++) {
    for (int j = -2; j <= 2; j++) {
      ll x = X + i;
      ll y = Y + j;
      if (x < 0) continue;
      if (y < 0) continue;
      ll k = 3;
      if (x == y) k = 0;
      else if ((x ^ y) <= K) k = 1;
      else k = 2;
      cmin(res, abs(i) + abs(j) + k);
    }
  }
  cout << min(ans + res, o) << "\n";
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