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
  int n, m;
  cin >> n >> m;
  vi x(n);
  rep(i, n) cin >> x[i];
  vi t(n * 2);
  rep(i, n) t[i + n] = x[i] % m;
  for (int i = n - 1; i; i--)
    t[i] = t[i * 2] * t[i * 2 + 1] % m;
  auto query = [&](int l, int r) {
    int cur = 1;
    for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
      if (l & 1)
        cur = cur * t[l++] % m;
      if (r & 1)
        cur = cur * t[--r] % m;
    }
    return cur;
  };
  
  string s;
  cin >> s;
  int l = 0, r = n - 1;
  rep(i, n) {
    cout << query(l, r) << " \n"[i + 1 == n];
    int v = 0;
    if (s[i] == 'L') {
      l++;
    } else {
      r--;
    }
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