#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 5;
int a[N];

int digit(char a) {
  if ('0' <= a && a <= '9')
    return a - '0';
  if ('a' <= a && a <= 'z')
    return a - 'a' + 10;
  return a - 'A' + 36;
}
int read() {
  string s;
  cin >> s;
  int x = 0;
  for (char a : s)
    x = x * 62 + digit(a);
  return x;
}

const int BASE = 2e8 + 3;
struct Hash {
  static const int MOD1 = 1000000007, MOD2 = 1000000009;
  int x, y;
  Hash() : x(0), y(0) {}
  Hash(int v) : x(v), y(v) {}
  Hash(int _x, int _y) : x(_x), y(_y) {}
  long long to_ll() const { return (((long long)x) << 31) + y; }
  friend bool operator==(const Hash &a, const Hash &b) {
    return a.x == b.x && a.y == b.y;
  }
  friend Hash operator+(const Hash &a, const Hash &b) {
    return Hash((a.x + b.x) % MOD1, (a.y + b.y) % MOD2);
  }
  friend Hash operator-(const Hash &a, const Hash &b) {
    return Hash((a.x - b.x + MOD1) % MOD1, (a.y - b.y + MOD2) % MOD2);
  }
  friend Hash operator*(const Hash &a, const Hash &b) {
    return Hash((long long)a.x * b.x % MOD1, (long long)a.y * b.y % MOD2);
  }
};
Hash pw[N];

Hash v[N];

Hash get_hash(int l, int r) { return v[r] - v[l - 1] * pw[r - l + 1]; }

int c[N];

bool isprime[N];
void init(int n) {
  fill(isprime + 1, isprime + n + 1, true);
  isprime[1] = false;
  for (int i = 2; i <= n; i++)
    if (isprime[i])
      for (int j = i + i; j <= n; j += i)
        isprime[j] = false;
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    a[i] = read();
  pw[0] = 1;
  for (int i = 1; i <= n; i++)
    pw[i] = pw[i - 1] * BASE;
  for (int i = 1; i <= n; i++)
    v[i] = v[i - 1] * BASE + a[i];
  init(n / 2);
  for (int k = 1; k <= n / 2; k++) {
    int l = k * 2 + 1, r = n, p = 0;
    auto check = [=](int x) {
      return get_hash(1, x - 2 * k) + get_hash(2 * k + 1, x) ==
             get_hash(k + 1, x - k) * 2;
    };
    while (l <= r) {
      int mid = (l + r) / 2;
      if (check(mid))
        p = mid, l = mid + 1;
      else
        r = mid - 1;
    }
    int ql = k * 2 + 1, qr = p;
    if (ql <= qr)
      c[ql]++, c[qr + 1]--;
  }
  for (int i = 1; i <= n; i++)
    c[i] += c[i - 1];
  for (int i = 1; i <= n; i++)
    if (c[i])
      cout << "1";
    else
      cout << "0";
  return 0;
}