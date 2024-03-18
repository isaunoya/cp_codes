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

const int P = 998244353;
void add(int &x, int y) {
  x += y;
  if (x >= P) {
    x -= P;
  }
}

void solve() {
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];
  vector<int> stk;
  vector<int> l(n, -1);
  vector<int> r(n, -1);
  for (int i = 0; i < n; i++) {
    while (!stk.empty() && a[stk.back()] > a[i]) {
      l[i] = stk.back();
      stk.pop_back();
    }
    if (!stk.empty()) {
      r[stk.back()] = i;
    }
    stk.emplace_back(i);
  }
  int root = stk[0];
  auto dfs = [&](auto &dfs, int u, bool hav_l, bool hav_r) -> ll {
    ll lc = 1, rc = 1;
    if (~l[u])
      lc = dfs(dfs, l[u], hav_l, true);
    if (~r[u])
      rc = dfs(dfs, r[u], true, hav_r);
    ll ans = lc * rc % P;
    if (hav_l)
      ans += rc - 1;
    if (hav_r)
      ans += lc - 1;
    if (hav_l || hav_r)
      ans += 1;
    return ans % P;
  };
  cout << dfs(dfs, root, false, false) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}