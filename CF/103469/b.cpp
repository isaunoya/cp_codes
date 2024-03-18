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

int n, k, w, q;
const int N = 131072;
const int P = 998244353;
int cnt[N * 2], s[N * 2][6], s2[N * 2][6][6];
int c[6][6], pw[N][6];

int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y % 2 == 1) {
      res = 1ll * res * x % P;
    }
    x = 1ll * x * x % P;
    y /= 2;
  }
  return res;
}

int inverse(int x) { return power(x, P - 2); }

void md(int &x) {
  if (x >= P) {
    x -= P;
  }
}

void pu(int x) {
  int sz = cnt[x * 2];
  cnt[x] = cnt[x * 2] + cnt[x * 2 + 1];
  memcpy(s[x], s[x * 2], sizeof s[x]);
  for (int i = 0; i <= k; i++) {
    for (int j = 0; j <= i; j++) {
      md(s[x][i] += 1ll * s[x * 2 + 1][j] * c[i][j] % P * pw[sz][i - j] % P);
    }
  }
  memcpy(s2[x], s2[x * 2], sizeof s2[x]);
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < w; j++) {
      md(s2[x][(i + sz) % w][j] += s2[x * 2 + 1][i][j]);
    }
  }
}
void upd(int x, const int &v) {
  int X = x + N;
  int &c = cnt[X];
  if (v == 1) {
    c += 1;
    for (int i = 0; i <= k; i++) {
      md(s[X][i] += 1ll * pw[c][i] * x % P);
    }
    s2[X][c % w][x % w] += 1;
  } else {
    for (int i = 0; i <= k; i++) {
      md(s[X][i] += P - 1ll * pw[c][i] * x % P);
    }
    s2[X][c % w][x % w] -= 1;
    c -= 1;
  }
  while (X >>= 1) {
    pu(X);
  }
}

void solve() {
  cin >> n >> k >> w;
  vi a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    upd(a[i], 1);
  }
  cin >> q;
  const int ivw = inverse(w);
  while (q--) {
    int x, y;
    cin >> x >> y;
    --x;
    upd(a[x], -1);
    upd(a[x] = y, 1);
    int ans = s[1][k];
    for (int i = 1; i < w; i++) {
      for (int j = 1; j < w; j++) {
        int c = s2[1][i][j];
        md(ans += P - 1ll * c * (1ll * pw[i][k] * j % w) % P);
      }
    }
    cout << 1ll * ans * ivw % P << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int i = 0; i < N; i++) {
    pw[i][0] = 1;
    for (int j = 1; j < 6; j++) {
      pw[i][j] = 1ll * pw[i][j - 1] * i % P;
    }
  }
  for (int i = 0; i < 6; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) {
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
  }
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}