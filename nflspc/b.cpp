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

const int b = 3;
const int P = 998244353;
pii mul(pii x, pii y) {
  ll r = (x.first + x.second * P) * (y.first + y.second * P);
  return pii(r % P, (r / P) % 2);
}
pii get(int p) {
  pii r = make_pair(1, 0); // x, (c&1) st x+cP=3^p
  pii x = make_pair(3, 0);
  while (p) {
    if (p % 2 == 1)
      r = mul(r, x);
    x = mul(x, x);
    p /= 2;
  }
  return r;
}

void solve() {
  int n;
  cin >> n;
  int m;
  cin >> m;
  vi a(n);
  rep(i, n) cin >> a[i];
  vi b(m);
  rep(i, m) cin >> b[i];
  vc<pii> p(n), q(m);
  rep(i, n) p[i] = get(a[i]);
  rep(i, m) q[i] = get(b[i]);
  // debug(p, q);
  
  debug(sp,sq);

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