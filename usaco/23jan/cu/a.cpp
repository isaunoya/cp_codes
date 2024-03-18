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
  int n;
  cin >> n;
  string s;
  cin >> s;
  int first_g = -1;
  int first_h = -1;
  int lst_g = -1;
  int lst_h = -1;
  rep(i, n) {
    if (s[i] == 'G') {
      if (first_g == -1) first_g = i;
      lst_g = i;
    } else {
      if (first_h == -1) first_h = i;
      lst_h = i;
    }
  }

  vi a(n);
  rep(i, n) cin >> a[i], --a[i];

  int ans = 0;

  bool first_h_with_first_g = false;
  rep(i, n) {
    if (s[i] == 'G') {
      bool ok = (i <= first_h && a[i] >= first_h && a[first_h] >= lst_h);

      if (ok) {
        ans += 1;
        if (i == first_g) {
          first_h_with_first_g = true;
        }
      }
    } else {
      bool ok = (i <= first_g && a[i] >= first_g && a[first_g] >= lst_g);

      if (ok) {
        ans += 1;
        if (i == first_h) {
          first_h_with_first_g = true;
        }
      }
    }
  }
  if (!first_h_with_first_g) {
    if (a[first_h] >= lst_h && a[first_g] >= lst_g) {
      ans += 1;
    }
  }

  cout << ans << "\n";
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