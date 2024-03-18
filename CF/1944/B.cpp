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
template <typename T> using vc = vector<T>;
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
  int n, k;
  cin >> n >> k;
  vi a(n * 2);
  rep(i, n * 2) {
    cin >> a[i];
    --a[i];
  }
  vi avail;
  vi cnt(n);
  rep(i, n) {
    cnt[a[i]]++;
  }
  vi A, B;
  rep(i, n) if (cnt[i] % 2 == 1) {
    avail.pb(i);
  } else if (cnt[i] == 2) {
    A.pb(i), A.pb(i);
  } else {
    B.pb(i), B.pb(i);
  }

  for (auto x : avail) {
    A.pb(x);
    B.pb(x);
  }

  A.resize(k * 2);
  B.resize(k * 2);
  for (int i : A) {
    cout << i + 1 << " ";
  }
  cout << "\n";
  for (int i : B) {
    cout << i + 1 << " ";
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