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

ll power(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y % 2) {
      r = r * x % P;
    }
    y = y / 2; 
    x = x * x % P;
  }
  return r;
}
ll inv(int x) {
  return power(x, P - 2);
}
ll binom(ll n, ll k) {
  ll res = 1;
  for (int i = n - k + 1; i <= n; i++) {
    res = res * i % P;
  }
  for (int i = 1; i <= k; i++) {
    res = res * inv(i) % P;
  }
  return res;
}
void solve() {
  int n, C;
  cin >> n >> C;
  vc<array<int, 3>> v(n);
  rep(i, n) {
    rep(j, 3) {
      cin >> v[i][j];
    }
    if (v[i][0] > 0) {
      --v[i][0];
    }
    if (v[i][1] > 0) {
      --v[i][1];
    }
  }

  vi list{1};
  auto dfs = [&](auto &dfs, int u) -> void {
    if (~v[u][0]) {
      dfs(dfs, v[u][0]);
    }
    list.pb(v[u][2]);
    if (~v[u][1]){
      dfs(dfs, v[u][1]);
    }
  };
  dfs(dfs, 0);
  list.pb(C);
  debug(list);

  ll res = 1;
  for (int l = 0, r; l < list.size(); l = r) {
    r = l + 1;
    while (r < list.size() && list[r] == -1) {
      r++;
    }
    if (r == list.size()) {
      break;
    }
    int len = r - l - 1;
    if (len == 0) {
      continue;
    }
    // debug(l, r, len);
    debug(list[r] - list[l] + len, len);
    res = res * binom(list[r] - list[l] + len, len) % P;
  }
  cout << res << "\n";
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