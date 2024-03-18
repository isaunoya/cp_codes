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

using vvi = vc<vi>;

void solve() {
  int n, k;
  cin >> n >> k;

  if (k % 2 == 1) {
    cout << "No\n";
    return;
  }
  if (n == 2) {
    cout << "Yes\n";
    if (k == 0) {
      cout << "0 0\n";
      cout << "0 0\n";
    } else if (k == 2) {
      cout << "1 0\n";
      cout << "0 1\n";
    } else if (k == 4) {
      cout << "1 1\n";
      cout << "1 1\n";
    }
    return;
  }

  int r = 0;

  if (k > n * n - k) {
    k = n * n - k;
    r = 1;
  }

  if (n > 2 && k == 2) {
    cout << "No\n";
    return;
  }
  if (n > 2 && k == 2) {
    cout << "No\n";
    return;
  }

  vvi a(n, vi(n));
  int x = 0, y = 0;
  auto next = [&]() {
    y += 2;
    if (y == n) {
      x += 2, y = 0;
    }
  };
  while (k) {
    if (k == 6) {
      rep(i, n - 3, n) rep(j, n - 3, n) if (i != j) a[i][j] = 1;
      k = 0;
      break;
    } else {
      rep(i, 2) rep(j, 2) a[x + i][y + j] = 1;
      k -= 4;
      next();
      if (k % 4 == 2) {
        while (x >= n - 4 && y >= n - 4) {
          next();
        }
      }
    }
  }

  cout << "Yes\n";
  for (auto v : a) {
    for (auto vi : v)
      cout << (vi ^ r) << " ";
    cout << "\n";
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