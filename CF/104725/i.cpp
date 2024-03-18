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

const int N = 1e7 + 5;
bool isprime[N];
int pr[N / 10], c = 0;
// const int P = 998244353;
// int power(int x, int y) {
//   int r = 1;
//   while (y) {
//     if (y % 2)
//       r = 1ll * r * x % P;
//     x = 1ll * x * x % P;
//     y /= 2;
//   }
//   return r;
// }
int inv(int x) { return power(x, P - 2); }

ll sp, sq;
int pw[N], ipw[N];

void md(int &x) {
  if (x >= P) {
    x -= P;
  }
}
void solve() {
  int n, l, r;
  cin >> n >> l >> r;
  vi p(n + 1), q(n + 1);

  for (int i = 1; i <= n; i++)
    cin >> p[i], sp += p[i];
  for (int i = 1; i <= n; i++)
    cin >> q[i], sq += q[i];
  sp %= P, sq %= P;
  for (int i = 1; i <= n; i++) {
    p[i] = 1ll * p[i] * inv(sp) % P;
    q[i] = 1ll * q[i] * inv(sq) % P;
  }

  vector<int> f(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    f[i] = 1ll * ipw[l + i] * p[i] % P;
  }
  vector<int> g(n + 1, 0);
  for (int j = 1; j <= n; j++) {
    int bas = upper_bound(pr, pr + c, r - j) - pr;
    g[j] = 1ll * pw[r + 1 - j - bas] * q[j] % P;
  }
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     int bas = upper_bound(pr, pr + c, r - j) - pr;
  //     d[i + j] += 1ll * pw[r - l + 1 - i - j - bas] * p[i] % P * q[j] % P;
  //     if (d[i + j] >= P) {
  //       d[i + j] -= P;
  //     }
  //   }
  // }
  vector<int> d = f * g;
  for (int i = 2; i <= n * 2; i++) {
    cout << d[n * 2 - i + 2] << " \n"[i == n * 2];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int i = 2; i < N; i++)
    isprime[i] = 1;
  for (int i = 2; i < N; i++) {
    if (isprime[i]) {
      pr[c++] = i;
      for (int j = i * 2; j < N; j += i) {
        isprime[j] = 0;
      }
    }
  }
  pw[0] = 1;
  rep(i, 1, N) pw[i] = pw[i - 1] + pw[i - 1], md(pw[i]);
  const int inv = (P + 1) / 2;
  ipw[0] = 1;
  rep(i, 1, N) ipw[i] = 1ll * ipw[i - 1] * inv % P;
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}