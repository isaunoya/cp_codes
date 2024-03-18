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
  int n;
  cin >> n;
  vi x(n), y(n);
  rep(i, n) cin >> x[i] >> y[i];
  vi t(n * 2);
  rep(i, n) {
    int val = 0;
    for (int j = 30; j >= 0; j--) {
      if ((x[i] >> j & 1) != (y[i] >> j & 1)) {
        break;
      }
      if (x[i] >> j & 1) 
        val |= 1 << j;
    }
    x[i] -= val;
    y[i] -= val;
    t[i + n] = val;
  }
  for (int i = n - 1; i >= 0; i--) {
    t[i] = t[i * 2] | t[i * 2 + 1];
  }
  auto query = [&](int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        ans |= t[l++];
      }
      if (r & 1) {
        ans |= t[--r];
      }
    }
    return ans;
  };
  vc<array<int, 31>> sum(n + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= 30; j++) {
      sum[i + 1][j] = sum[i][j];
      if (y[i] >> j & 1) {
        sum[i + 1][j]++;
      }
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l;
    int cur = query(l, r);
    for (int j = 30; j >= 0; j--) {
      int cnt = sum[r][j] - sum[l][j];
      int w = (cur >> j & 1);
      if (cnt + w >= 2) {
        cur |= (1 << j + 1) - 1;
        break;
      } else if (cnt == 1) {
        cur |= 1 << j;
      }
    }
    cout << cur << " \n"[q == 0];
  }
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