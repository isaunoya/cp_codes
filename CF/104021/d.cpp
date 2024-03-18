#include <bits/stdc++.h>

typedef long long int64;

const int N = 100000, mod = 59964251, Mod = (643 - 1) * (mod / 643 - 1);

int Power(int a, int64 k) {
  int res = 1;
  for (; k; k >>= 1, a = 1LL * a * a % mod)
    if (k & 1)
      res = 1LL * res * a % mod;
  return res;
}

int n, m, d, k;
int b[N + 9], pr[N + 9], cp;
int mu[N + 9], f[N + 9];

void Sieve() {
  cp = 0;
  mu[1] = 1;
  for (int i = 1; i <= m; ++i)
    b[i] = 0;
  for (int i = 2; i <= m; ++i) {
    if (!b[i]) {
      pr[++cp] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cp && i * pr[j] <= m; ++j) {
      b[i * pr[j]] = 1;
      if (i % pr[j] == 0) {
        mu[i * pr[j]] = 0;
        break;
      }
      mu[i * pr[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= m; ++i)
    f[i] = (f[i - 1] + Power(i, k)) % mod;
}

void work() {
  std::string s;
  std::cin >> s >> m >> d >> k;
  n = 0;
  for (int i = 0; i < s.size(); ++i)
    n = (10LL * n + s[i] - '0') % Mod;
  k %= Mod;
  m /= d;
  if (!m) {
    std::cout << 0 << '\n';
    return;
  }
  Sieve();
  int nk = 1LL * n * k % Mod;
  int con = 1LL * Power(d, nk);
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    if (!mu[i])
      continue;
    int t = 1LL * Power(i, nk) * Power(f[m / i], n) % mod;
    if (mu[i] == -1)
      t = mod - t;
    ans = (ans + t) % mod;
  }
  std::cout << 1LL * ans * con % mod << '\n';
}

int main() {
  std::ios::sync_with_stdio(0);
  int T = 1;
  std::cin >> T;
  for (; T--;)
    work();
  return 0;
}