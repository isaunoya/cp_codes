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
  string s;
  cin >> s;
  int n = sz(s);
  vc<vi> lcp(n + 1, vi(n + 1));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = n - 1; j >= 0; j--) {
      if (s[i] == s[j]) {
        lcp[i][j] = lcp[i + 1][j + 1] + 1;
      }
    }
  }

  // rep(i, n) rep(j, n) debug(i, j, lcp[i][j]);
  // lcp(s1, s2) = s1
  // s2 + s3 = s5 + s6
  
  // lcp[i][j] >= j-i -> coef[j][j+(j-i)]+=1

  vc<vi> coef(n + 1, vi(n + 1));
  rep(starter_1, n) {
    rep(starter_2, starter_1 + 1, n) {
      if (lcp[starter_1][starter_2] >= starter_2 - starter_1) {
        // debug(starter_1, starter_2);
        coef[starter_2][starter_2 + (starter_2 - starter_1)] += 1;
      }
    }
  }
  rep(i, n) {
    rep(j, i + 1, n) {
      coef[i][j] += coef[i][j - 1];
    }
    rep(j, i + 1, n) {
      coef[i][j] += coef[i][j - 1];
    }
  }

  ll ans = 0;
  rep(starter_2, n) {
    rep(starter_5, starter_2 + 1, n) {
      int max_len = starter_5 - starter_2 - 1;
      int lc = lcp[starter_2][starter_5];
      if (lc >= max_len) {
        lc = max_len;
      }
      if (lc < 2) continue;
      // debug(starter_2, starter_5, lc);
      // rep(i, 1, lc) {
      //   ans += coef[starter_2][starter_2 + i];
      // }
      ans += coef[starter_2][starter_2 + lc - 1];
    }
  }

  cout << ans << "\n";
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