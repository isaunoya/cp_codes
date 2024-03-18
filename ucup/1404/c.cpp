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

const int P = 998244353;
vi d[200005];
int pw[200005];

int p[33];

void upd(int x) {
  for (int j = 29; j >= 0; j--) {
    if (x >> j & 1) {
      if (!p[j]) {
        p[j] = x;
        return;
      }
      x ^= p[j];
    }
  }
}

void clear() {
  memset(p, 0, sizeof p);
}

void solve() {
  int n;
  cin >> n;
  vi a(n);
  vi c(n + 1);
  rep(i, n) cin >> a[i], ++c[a[i]];

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (c[i] == 0)
      continue;
    int coef = pw[c[i] - 1];
    int cnt = 0;
    clear();
    for (int j : d[i]) {
      if (c[j] == 0) continue;
      upd(j);
      cnt += c[j];
    }
    int c = 0;
    rep(j, 30) c += !!p[j];
    ans += 1ll * coef * pw[cnt - c] % P;
    if (ans >= P) {
      ans -= P;
    }
  }

  clear();
  rep(i, n) {
    int x = a[i];
    upd(x);
  }

  int cnt = 0;
  for (int i = 0; i < 30; i++) {
    if (p[i]) {
      cnt += 1;
    }
  }

  ans += pw[n - cnt] - 1;
  if (ans >= P) {
    ans -= P;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int i = 1; i < 200005; i++) {
    for (int j = i * 2; j < 200005; j += i) {
      d[j].pb(i);
    }
  }
  pw[0] = 1;
  for (int i = 1; i < 200005; i++) {
    pw[i] = pw[i - 1] + pw[i - 1];
    if (pw[i] >= P) {
      pw[i] -= P;
    }
  }
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}