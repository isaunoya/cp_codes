#include <algorithm>
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
  vi a(n);
  rep(i, n) cin >> a[i];
  vi ans;

  int p = -1;
  rep(i, n - 1) if (a[i] > a[i + 1]) p = i;
  if (p == -1)
    ans.pb(0);
  vi b;
  b.insert(b.end(), a.begin() + p + 1, a.end());
  b.insert(b.end(), a.begin(), a.begin() + p + 1);
  if (is_sorted(all(b))) {
    ans.pb(p + 3);
    ans.pb(n - 1 - p);
  }

  rep(i, n) a[i] = -a[i];
  p = -1;
  rep(i, n - 1) if (a[i] > a[i + 1]) p = i;
  // debug(a, p, a[p], a[p + 1]);
  if (p == -1)
    ans.pb(0 + 1);
  b.clear();
  b.insert(b.end(), a.begin() + p + 1, a.end());
  b.insert(b.end(), a.begin(), a.begin() + p + 1);
  // debug(b);
  if (is_sorted(all(b))) {
    ans.pb(p + 2);
    ans.pb(n - 1 - p + 1);
  }


  if (ans.empty()) {
    cout << -1 << "\n";
  } else {
    cout << *min_element(all(ans)) << "\n";
  }
}
/*
1
4
2 5 5 4
*/

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