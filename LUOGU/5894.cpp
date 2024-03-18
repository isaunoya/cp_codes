#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define eb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  if (x > y)
    x = y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  if (x < y)
    x = y;
}
using ll = long long;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

void solve() {
  int A, B, N;
  cin >> A >> B >> N;
  vector<int> a(A);
  vector<int> b(B);
  for (int i = 0; i < A; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < B; i++) {
    cin >> b[i];
  }
  vector<pair<int, int>> c(N);
  for (int i = 0; i < N; i++) {
    cin >> c[i].first >> c[i].second;
  }

  sort(all(a));
  sort(all(b));
  sort(all(c));

  auto check = [&](int m) {
    priority_queue<int> q;
    int p = 0;
    for (int i = 0; i < A; i++) {
      while (p < N && c[p].first < a[i]) {
        q.emplace(c[p++].second);
      }
      int t = m;
      while (!q.empty() && t) {
        q.pop();
        t -= 1;
      }
    }
    while (p < N) {
      q.emplace(c[p++].second);
    }
    if (q.empty()) {
      return true;
    }
    for (int i = B - 1; i >= 0; i--) {
      int t = m;
      while (!q.empty() && t && q.top() < b[i]) {
        q.pop();
        t -= 1;
      }
    }
    return q.empty();
  };
  int l = 0, r = N + 1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (check(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  if (r == N + 1) {
    r = -1;
  }
  cout << r << "\n";
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