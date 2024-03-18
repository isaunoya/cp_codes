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
  int n;
  cin >> n;
  vi a(n), b(n);
  rep(i, n) cin >> a[i];
  rep(i, n) cin >> b[i];
  vi op1(n);
  vi op2(n);
  vi coef(n);
  rep(i, n) {
    op1[i] = ((a[i] - 1) - 0) - (a[i] - b[i]);
    op2[i] = (0 - (b[i] - 1)) - (a[i] - b[i]);
    coef[i] = op1[i] - op2[i];
  }
  // debug(op1, op2, coef);
  vi p(n); iota(all(p), 0);
  sort(all(p), [&](int x, int y) {
    return coef[x] > coef[y];
  });
  int o = 0;
  for (int i : p) {
    if (o == 0) {
      a[i] -= 1, b[i] = 0;
    } else {
      b[i] -= 1, a[i] = 0;
    }
    o ^= 1;
  }

  ll A = accumulate(all(a), 0LL);
  ll B = accumulate(all(b), 0LL);

  cout << A - B << "\n";
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