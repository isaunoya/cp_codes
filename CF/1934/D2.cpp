#include <algorithm>
#if defined(LOCAL)
#include <D:/cp/templates/my_template_compiled.hpp>
#else
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#define debug(...) 42
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
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second
#endif

void solve() {
  ll n, m;
  cin >> n >> m;
  vl p;
  ll hb_m = 0;
  for (int i = 0; i < 62; i++) {
    if (n >> i & 1) {
      p.push_back(i);
    }
    if (m >> i & 1) {
      hb_m = i;
    }
  }

  reverse(all(p));
  if (p[0] == hb_m) {
    cout << 1 << "\n";
    cout << n << " " << m << "\n";
    return;
  }

  if (p.size() == 1 || p[1] < hb_m) {
    cout << -1 << "\n";
    return;
  }

  vl path = {n};
  for (int i = 1; i < (int)p.size() && p[i] >= hb_m; i++) {
    path.push_back((1LL << p[i] + 1) - 1);
  }
  path.push_back(m);
  path.resize(unique(all(path)) - path.begin());
  cout << path.size() - 1 << "\n";
  for (auto i : path) {
    cout << i << " ";
  }
  cout << "\n";
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