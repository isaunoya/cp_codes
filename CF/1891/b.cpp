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
  int n, q;
  cin >> n >> q;
  vi a(n);
  rep(i, n) cin >> a[i];
  vi qq;
  rep(i, q) {
    int x;
    cin >> x;
    if (qq.empty()) qq.emplace_back(x);
    else {
      if (qq.back() <= x) continue;
      qq.emplace_back(x);
    }
  }
  // debug(qq);
  ll w[31];
  memset(w, 0, sizeof w);
  for (int j = 0; j <= 30; j++) {
    w[j] = 0;
    for (int x : qq) {
      if (j >= x) {
        w[j] += 1 << x - 1;
      }
    }
  }
  rep(i, n) {
    cout << a[i] + w[__lg(a[i] & -a[i])] << " \n"[i + 1 == n];
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