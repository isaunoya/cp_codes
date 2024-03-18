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

int f[2005][2005];

const int P = 998244353;
int power(int x, int y) {
  int r = 1;
  while (y) {
    if (y % 2 == 1) {
      r = 1ll * r * x % P;
    }
    y /= 2;
    x = 1ll * x * x % P;
  }
  return r;
}
int inv(int x) {
  return power(x, P - 2);
}

void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  int a = 0, b = 0;
  rep(i, n) {
    if (s[i] == 'A') {
      a++;
    } else {
      b++;
    }
  }
  
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int i = 1; i <= 2000; i++) {
    for (int j = 1; j <= i; j++) {
      if (i == j) {
        f[i][j] = 0;
      } else {
        f[i][j] = 1ll * (f[i - 1][j] + 1) * (i - j) % P * inv(i) % P;
        f[i][j] += 1ll * (f[i - 1][j - 1] + 2) * j % P * inv(i) % P;
        if (f[i][j] >= P) {
          f[i][j] -= P;
        }
      }
    }
  }
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}