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

int n, P;
int power(int x, int y) {
  ll r = 1;
  while (y) {
    if (y % 2 == 1)
      r = r * x % P;
    x = 1ll * x * x % P;
    y /= 2;
  }
  return r;
}
const int N = 2e5 + 5;
int fac[N], ifac[N], inv[N];
int ans[N];
int sum = 0, num = 0;

void upd(int &x, const int &y) {
  x += y;
  if (x >= P)
    x -= P;
}

int ways = 1;
int cnt[N*2];
void dfs(int x, int lst) {
  if (x > 1 && sum <= x && num + x - sum <= n) {
    int k = num + x - sum;
    // debug(k,x,lst);
    upd(ans[k], 1ll * ways * ifac[x - sum] % P);
  }
  // debug(x,lst,2*n/x);
  for (int i = lst, o = ways; i <= 2 * n / x; i++) {
    ways = 1ll * ways * inv[++cnt[i]] % P;
    num += 1, sum += i;
    dfs(x * i, i);
    ways = o;
    num -= 1, sum -= i;
    --cnt[i];
  }
}

void solve() {
  cin >> n >> P;
  fac[0] = ifac[0] = inv[0] = 1;
  rep(i, 1, N) fac[i] = 1ll * fac[i - 1] * i % P,
               ifac[i] = power(fac[i], P - 2), inv[i] = power(i, P - 2);
  dfs(1, 2);
  for (int i = 2; i <= n; i++)
    cout << 1ll * ans[i] * fac[i] % P << " \n"[i == n];
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