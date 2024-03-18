#include <algorithm>
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
  if (n * m % 2 == 1) {
    cout << "NO\n";
    return;
  }
  if (m <= 30 && (1 << m) < n) {
    cout << "NO\n";
    return;
  }
  if (n <= 30 && (1 << n) < m) {
    cout << "NO\n";
    return;
  }

  cout << "YES\n";
  bool swp = false;
  if (n < m) {
    swp = true;
    swap(n, m);
  }

  vc<vi> a;
  int lg = __lg(m);
  while ((1 << lg) < m) {
    lg++;
  }

  for (int i = lg - 1; i >= 0; i--) {
    vi x(m), y(m);
    rep(j, m) {
      x[j] = j >> i & 1;
      y[j] = !x[j];
    }
    debug(x, y);
    a.pb(x);
    a.pb(y);
  }
  if (n % 2 == 1) {
    a.pop_back();
  }
  sort(all(a));
  int cur = 0;
  int p = 0, q = a.size() - 1;
  int t = a.size();
  while (a.size() < n) {
    vi x(m), y(m);
    for (int j = 0; j < m; j++) {
      if (j < 30 && cur >> j & 1) {
        x[m - 1 - j] = 1;
      }
      y[m - 1 - j] = !x[m - 1 - j];
    }
    cur += 1;
    while (p < t && a[p] < x) {
      p++;
    }
    if (p < t && a[p] == x) {
      continue;
    }
    while (q >= 0 && a[q] > y) {
      q--;
    }
    if (q >= 0 && a[q] == y) {
      continue;
    }
    a.pb(x);
    a.pb(y);
  }

  if (!swp) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << a[i][j];
      }
      cout << "\n";
    }
  } else {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cout << a[j][i];
      }
      cout << "\n";
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