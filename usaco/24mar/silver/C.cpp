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
  int N;
  cin >> N;
  string s;
  cin >> s;
  vi ans(N + 1);
  for (int L = 1; L <= N; L++) {
    vc<string> S;
    rep(i, N - L + 1) S.pb(s.substr(i, L));
    vector<int> p(N - L + 1);
    iota(all(p), 0);
    sort(all(p), [&](int i, int j) {
      if (S[i] != S[j])
        return S[i] < S[j];
      else
        return i < j;
    });
    vi rk(N - L + 1);
    rep(i, N - L + 1) rk[p[i]] = i;
    for (int K = N; K >= L; K--) {
      int cur = 0;
      rep(i, N - L + 1) {
        int l = max(i - (K - L) - 1, -1);
        for (int j = i - 1; j >= max(i - (K - L), 0); j--) {
          if (rk[j] < rk[i]) {
            l = j;
            break;
          }
        }
        int r = min(i + K - L + 1, N - L + 1);
        for (int j = i + 1; j <= min(i + K - L, N - L); j++) {
          if (rk[j] < rk[i]) {
            r = j;
            break;
          }
        }
        if (r - l >= K - L + 2) {
          cur++;
        }
      }
      debug(K, L, cur);
      ans[cur]++;
    }
  }
  for (int i = 1; i <= N; i++) {
    cout << ans[i] << "\n";
  }
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