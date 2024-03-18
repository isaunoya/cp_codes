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

namespace Poly {
const int P = 998244353;
const int G = 3;
int power(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % P)
    if (y & 1)
      res = 1ll * res * x % P;
  return res;
}
int inc(int x, int y) { return ((x += y) >= P) ? x - P : x; }
int dec(int x, int y) { return ((x -= y) < 0) ? x + P : x; }
vector<int> rev, rt;
int lim = 1;
void init(const int &len) {
  int l = 0;
  lim = 1;
  while (lim <= len) {
    lim <<= 1, l++;
  }
  rev.resize(lim), rt.resize(lim);
  for (int i = 0; i < lim; i++)
    rev[i] = rev[i >> 1] >> 1 | (i & 1) << l - 1;
  for (int len = 1; len < lim; len <<= 1) {
    int w = power(G, (P ^ 1) / (len << 1));
    rt[len] = 1;
    for (int i = 1; i < len; i++) {
      rt[i + len] = 1ll * rt[i + len - 1] * w % P;
    }
  }
}
void ntt(vector<int> &f) {
  f.resize(lim);
  for (int i = 0; i < lim; i++)
    if (i < rev[i]) {
      swap(f[i], f[rev[i]]);
    }
  for (int len = 1; len < lim; len <<= 1) {
    for (int i = 0; i < lim; i += len << 1) {
      for (int j = 0; j < len; j++) {
        int x = f[i + j], y = 1ll * f[i + j + len] * rt[j + len] % P;
        f[i + j] = inc(x, y), f[i + j + len] = dec(x, y);
      }
    }
  }
}

vector<int> operator*(vector<int> f, vector<int> g) {
  int n = f.size(), m = g.size(), inv;
  init(n + m - 2), inv = power(lim, P - 2), ntt(f), ntt(g);
  for (int i = 0; i < lim; i++)
    f[i] = 1ll * f[i] * g[i] % P;
  reverse(f.begin() + 1, f.end()), ntt(f), f.resize(n + m - 1);
  for (int &x : f)
    x = 1ll * x * inv % P;
  return f;
}
} // namespace Poly
using namespace Poly;


// 976 ms
const int B = 4000;
void solve() {
  int N;
  cin >> N;
  vi a(N);
  rep(i, N) { cin >> a[i]; }
  int mx = *max_element(all(a)) + 1;
  vi b(mx);
  rep(i, N) b[a[i]] += 1;
  vi ans(mx * 2);
  for (int l = 0, r; l < mx; l = r) {
    r = min(l + B, mx);
    vi f(b.begin(), b.begin() + l);
    vi g(b.begin() + l, b.begin() + r);
    rep(i, sz(g)) g[i] = 1ll * (i + l) * g[i] % P;
    auto res = f * g;
    rep(i, sz(res)) {
      ans[i + l] += res[i];
      if (ans[i + l] >= P) {
        ans[i + l] -= P;
      }
    }
    rep(i, l, r) {
      rep(j, i + 1, r) {
        ans[i + j] += 1ll * b[i] * j % P * b[j] % P;
        if (ans[i + j] >= P) {
          ans[i + j] -= P;
        }
      }
    }
  }
  int res = 0;
  rep(i, mx * 2) {
    res += 1ll * ans[i] * power(i, P - 2) % P;
    if (res >= P) {
      res -= P;
    }
  }
  cout << res << "\n";
}


/*
// 321 ms

void solve() {
  int N;
  cin >> N;
  vi a(N);
  rep(i, N) { cin >> a[i]; }
  int mx = *max_element(all(a)) + 1;
  vi b(mx);
  rep(i, N) b[a[i]] += 1;
  vi c = b;
  rep(i, mx) c[i] = 1ll * c[i] * i % P;
  vi ans(mx * 2);
  auto solve = [&](auto &self, int l, int r) -> void {
    if (l + 1 == r) {
      return;
    }
    int m = (l + r) / 2;
    self(self, l, m), self(self, m, r);
    vi f(b.begin() + l, b.begin() + m);
    vi g(c.begin() + m, c.begin() + r);
    auto res = f * g;
    rep(i, sz(res)) {
      ans[i + l + m] += res[i];
      if (ans[i + l + m] >= P) {
        ans[i + l + m] -= P;
      }
    }
  };
  solve(solve, 0, mx);
  long long res = 0;
  for (int i = 1; i < mx * 2; i++) {
    res += 1ll * ans[i] * power(i, P - 2) % P;
    if (res >= P) {
      res -= P;
    }
  }
  cout << res << "\n";
}

*/

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