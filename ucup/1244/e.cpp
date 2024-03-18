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

void solve() {
  string s;
  cin >> s;
  int n = sz(s);
  vector<int> sum(n + 1);
  rep(i, n) {
    sum[i + 1] = sum[i];
    if (s[i] == 'p') {
      sum[i + 1] += 1;
    }
  }

  ll ans = 0;
  rep(i, n) {
    if (s[i] == 'p' || s[i] == '?') {
      int L = 0;
      int R = 0;

      {
        int l = -1, r = i;
        while (r - l > 1) {
          int m = (l + r) / 2;
          if (sum[i] - sum[m] == 0) {
            r = m;
          } else {
            l = m;
          }
        }
        L = r;
      }

      {
        int l = i, r = n;
        while (r - l > 1) {
          int m = (l + r) / 2;
          if (sum[m + 1] - sum[i + 1] == 0) {
            l = m;
          } else {
            r = m;
          }
        }
        R = l;
      }

      // debug(i, L, R);
      int r = R - i;
      int l = i - L;

      ans += min(l / 2, r);
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