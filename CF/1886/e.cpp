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

void solve() {
  int n, m;
  cin >> n >> m;
  vc<pii> a(n);
  rep(i, n) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(all(a));
  vc<vc<pii>> avail(m, vector<pii>(n, {n + 1, n + 1}));
  rep(i, m) {
    int x;
    cin >> x;
    vc<pii> t;
    for (int k = 1; k <= n; k++) {
      int value = (x + k - 1) / k;
      if (t.empty() || t.back().first != value) {
        t.pb(value, k);
      }
    }
    for (auto [value, k] : t) {
      int l = lower_bound(all(a), pii(value, 0)) - a.begin();
      if (l < n) {
        cmin(avail[i][l], pii(k, k));
      }
    }
    rep(j, 1, n) { cmin(avail[i][j], avail[i][j - 1]); }
    for (int j = n - 2; j >= 0; j--) {
      cmin(avail[i][j], pii(avail[i][j + 1].first + 1, avail[i][j + 1].second));
    }
  }
  vc<array<int, 3>> dp(1 << m, array<int, 3>{n + 1, -1, -1});
  dp[0] = array<int, 3>{0, -1, -1};
  rep(s, 1, 1 << m) {
    rep(j, m) {
      if (s >> j & 1) {
        int t = s ^ (1 << j);
        int lst = dp[t][0];
        if (lst < n) {
          cmin(dp[s], array<int, 3>{lst + avail[j][lst].first, j,
                                    avail[j][lst].second});
        }
      }
    }
  }
  if (dp.back()[0] <= n) {
    cout << "YES\n";
    int s = (1 << m) - 1;
    vc<vi> ans(m);
    int N = n;
    while (s) {
      int j = dp[s][1], k = dp[s][2];
      rep(i, k) { ans[j].pb(a[--N].second); }
      s ^= 1 << j;
    }
    rep(i, m) {
      cout << sz(ans[i]) << " ";
      for (auto j : ans[i]) {
        cout << j + 1 << " ";
      }
      cout << "\n";
    }
  } else {
    cout << "NO\n";
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