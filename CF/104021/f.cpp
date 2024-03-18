#include <bits/stdc++.h>
using namespace std;

const int P = 998244353;
const int inv2 = (P + 1) / 2;
const int inv6 = (P + 1) / 6;

long long get1(long long l, long long r) {
  long long res = (l + r) % P;
  res = 1ll * res * ((r - l + 1) % P) % P;
  return res * inv2 % P;
}

long long get2(long long x) {
  long long res = (x + 1) % P;
  res = 1ll * res * ((2 * x + 1) % P) % P;
  res = 1ll * res * (x % P) % P;
  res = 1ll * res * inv6 % P;
  return res;
}

int main() {
  long long n;
  cin >> n;
  long long t = sqrt(n);
  long long ans = 0;
  for (long long a = 2; a <= t; a++) {
    long long w = 1, res = 0;
    for (__int128 l = a, r = a * a; l <= n; l = r, r = r * a, w++) {
      long long bound = min(r, (__int128)n + 1) - l;
      bound %= P;
      res += 1ll * bound * w % P;
      if (res >= P) {
        res -= P;
      }
    }
    ans += res * a % P;
    if (ans >= P) {
      ans -= P;
    }
  }
  ans += get1(t + 1, n) * ((n + 1) % P) % P;
  if (ans >= P)
    ans -= P;
  ans -= get2(n);
  if (ans < 0)
    ans += P;
  ans += get2(t);
  if (ans >= P)
    ans -= P;

  cout << ans << "\n";
}