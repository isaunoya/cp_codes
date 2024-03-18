#include <bits/stdc++.h>
#include <iomanip>
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

const double PI = acos(-1.0L);
using C = complex<double>;

struct Fft {
  int n;
  vector<int> rev;
  vector<C> omega;
  Fft(int n_) : n(n_), rev(n), omega(n) {
    rev[0] = 0;
    for (int i = 1, j = 0; i < n; ++i) {
      for (int k = n >> 1; (j ^= k) < k; k >>= 1) {
      }
      rev[i] = j;
    }
    for (int i = 0; i < n; ++i)
      omega[i] = polar(1.0, 2.0 * PI / n * i);
  }
  void fft(vector<C> &as) const {
    for (int m = n, l = 1; m >>= 1; l <<= 1) {
      for (int i = 0; i < n; i += m << 1) {
        for (int j = 0, k = 0; j < m; ++j, k += l) {
          const C t = as[i + j];
          as[i + j] += as[m + i + j];
          as[m + i + j] = omega[k] * (t - as[m + i + j]);
        }
      }
    }
    for (int i = 0; i < n; ++i)
      if (i < rev[i])
        swap(as[i], as[rev[i]]);
  }
};

const int B = 2500;
void solve() {
  int n, q;
  cin >> n >> q;
  int N = 1 << n;
  vi a(N);
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  cout << fixed << setprecision(4);
  vc<C> A(N);
  Fft FFT(N);
  vc<pii> mdf;
  rep(t, q) {
    if (t % B == 0) {
      rep(j, mdf.size()) {
        int i = mdf[j].first;
        int x = mdf[j].second;
        a[i] += x;
      }
      mdf.clear();
      rep(i, N) { A[i] = C(a[i], 0); }
      FFT.fft(A);
    }
    int op;
    cin >> op;
    if (op == 1) {
      int i, x;
      cin >> i >> x;
      mdf.pb(i, x);
    } else {
      int i;
      cin >> i;
      C ans = A[i];
      rep(k, mdf.size()) {
        int j = mdf[k].first;
        int x = mdf[k].second;
        ans += FFT.omega[(1ll * i * j) % N] * (double)x;
      }
      cout << ans.real() << " " << ans.imag() << "\n";
    }
  }
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