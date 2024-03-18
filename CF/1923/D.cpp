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
  vc<ll> s(n + 1);
  rep(i, n) s[i + 1] = s[i] + a[i];

  vi t(n * 2), tt(n * 2);
  rep(i, n) t[i + n] = tt[i + n] = a[i];
  for (int i = n - 1; i >= 0; i--) {
    t[i] = min(t[i * 2], t[i * 2 + 1]);
    tt[i] = max(tt[i * 2], tt[i * 2 + 1]);
  }

  auto query = [&](int l, int r) {
    if (r - l == 1) {
      return true;
    }
    int mx = 0, mn = inf;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        cmin(mn, t[l]);
        cmax(mx, tt[l]);
        l += 1;
      }
      if (r & 1) {
        r -= 1;
        cmin(mn, t[r]);
        cmax(mx, tt[r]);
      }
    }
    return mn != mx;
  };

  vi ans(n, n + 1);
  rep(i, n) {
    if (i + 1 < n && a[i + 1] > a[i]) {
      cmin(ans[i], 1);
    }
    if (i - 1 >= 0 && a[i - 1] > a[i]) {
      cmin(ans[i], 1);
    }
    {
      int l = -1, r = i;
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (s[i] - s[m] > a[i] && query(m, i)) {
          l = m;
        } else {
          r = m;
        }
      }
      if (l != -1)
        cmin(ans[i], i - l);
    }
    {
      int l = i, r = n + 1;
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (s[m] - s[i + 1] > a[i] && query(i + 1, m)) {
          r = m;
        } else {
          l = m;
        }
      }
      if (r != n + 1)
        cmin(ans[i], r - 1 - i);
    }
  }

  rep(i, n) {
    cout << ((ans[i] == n + 1) ? -1 : ans[i]) << " \n"[i + 1 == n];
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