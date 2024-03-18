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
mt19937_64 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

using ull = unsigned long long;
const int P = 998244353;
void solve() {
  int n;
  cin >> n;
  vc<ull> w(n);
  rep(i, n) w[i] = rng();
  vi c(2 * n);
  rep(i, 2 * n) cin >> c[i], --c[i];
  vc<ull> s(2 * n + 1);
  rep(i, 2 * n) s[i + 1] = s[i] ^ w[c[i]];
  debug(s);

  int ans = count(all(s), 0) - 1;
  int ways = 1;

  map<ull, int> lst;
  rep(i, 2 * n + 1) lst[s[i]] = i;
  rep(i, 2 * n) {
    if (s[i] == 0) {
      int cnt = 1;
      int j = i + 1;
      while (s[j] != 0) {
        cnt += 1;
        j = lst[s[j]];
        j += 1;
      }
      ways = 1ll * ways * cnt % P;
    }
  }

  // debug(ans, ways);

  cout << ans << " " << ways << "\n";
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