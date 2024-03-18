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
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i], --a[i];
  vi b(n);
  iota(all(b), 0);
  vi ans(n);
  int idx = 0;
  while (a.size()) {
    vi na, nb;
    rep(i, n) if (a[i] != i) {
      na.pb(a[i]);
      nb.pb(b[i]);
    }
    a.swap(na);
    b.swap(nb);
    vi c = a;
    sort(all(c));
    n = a.size();
    rep(i, n) a[i] = lower_bound(all(c), a[i]) - c.begin();
    int dt = inf;
    rep(i, n) {
      int now = (a[i] - i + n) % n;
      cmin(dt, now);
    }
    debug(dt, a, b);
    idx += dt;
    rep(i, n) {
      int now = (a[i] - i + n) % n;
      if (now == dt) {
        ans[b[i]] = idx;
      }
    }
    na = a, nb = b;
    rep(i, n) a[(i + dt) % n] = na[i];
  }
  for (int i : ans) {
    cout << i << " ";
  }
  cout << "\n";
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