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

void solve(int test) {
  int n, k;
  cin >> n >> k;
  vi len(k);
  rep(i, k) cin >> len[i];
  vi euler;
  vi ord(n - 1);
  rep(i, n - 1) ord[i] = i;
  rep(i, n - 1) {
    euler.pb(0);
    int l = 0, r = n - 2;
    while (l < r) euler.pb(ord[l] + 1), euler.pb(ord[r] + 1), l++, r--;
    rep(j, n - 1) ord[j] = (ord[j] + 1) % (n - 1);
  }
  int lst = 1, p = 1;
  cout << "Case #" << test + 1 << ":\n";
  rep(i, k) {
    cout << lst << " ";
    rep(j, len[i]) {
      cout << euler[p] + 1 << " ";
      lst = euler[p] + 1;
      p += 1;
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  rep(t) solve(i);
  return 0;
}