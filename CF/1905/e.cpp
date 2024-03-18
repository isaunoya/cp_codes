#include <bits/stdc++.h>
#include <unordered_map>
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

const int P = 998244353;
ll power(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y % 2 == 1) {
      r = 1ll * r * x % P;
    }
    x = 1ll * x * x % P;
    y /= 2;
  }
  return r;
}
unordered_map<ll, pair<ll, ll>> res;

pair<ll, ll> get(ll n) {
  if (n == 1) {
    return res[n] = make_pair(1, 0);
  }
  if (res.count(n)) {
    return res[n];
  }
  ll m = (n + 1) / 2;
  auto [L, L2] = get(m);
  auto [R, R2] = get(n - m);
  return res[n] = make_pair(
      (2 * (L + R) + (power(2, n) + P - power(2, m) + P - power(2, n - m) + 1)) % P,
      (L2 + R + R2) % P);
}

void solve() {
  ll n;
  cin >> n;
  auto ans = get(n);
  cout << (ans.fi + ans.se) % P << "\n";
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