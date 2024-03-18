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
  vector<long long> a(n);
  vector<pair<int, int>> ans;
  rep (i, 0, n) cin >> a[i];
  int pos = 0, neg = 0;
  rep (i, 0, n) if (a[i] > 0) pos += 1;
  rep (i, 0, n) if (a[i] < 0) neg += 1;
  auto print = [&]() {
    cout << sz(ans) << "\n";
    for (auto [x, y] : ans) {
      cout << x + 1 << " " << y + 1 << "\n";
    }
    return;
  };
  if (*min_element(a.begin(), a.end()) >= 0) {
    rep (i, 1, n) ans.emplace_back(i, i - 1);
    return print();
  }
  if (*max_element(a.begin(), a.end()) <= 0) {
    for (int i = n - 1; i >= 1; i--) ans.emplace_back(i - 1, i);
    return print();
  }
  if (neg && pos <= 7) {
    int p = -1;
    rep (i, 0, n) if (a[i] < 0) {
      p = i;
      break;
    }
    rep (i, 0, 5) a[p] *= 2, ans.emplace_back(p, p);
    rep (i, 0, n) if (a[i] > 0) {
      a[i] += a[p];
      ans.emplace_back(i, p);
    }
    for (int i = n - 1; i >= 1; i--) ans.emplace_back(i - 1, i);
    return print();
  }
  if (pos && neg <= 7) { // neg <= 7
    int p = -1;
    rep (i, 0, n) if (a[i] > 0) {
      p = i;
      break;
    }
    rep (i, 0, 5) a[p] *= 2, ans.emplace_back(p, p);
    rep (i, 0, n) if (a[i] < 0) {
      a[i] += a[p];
      ans.emplace_back(i, p);
    }
    rep (i, 1, n) ans.emplace_back(i, i - 1);
    return print();
  }
  // 8 <= pos <= 12 && 8 <= neg <= 12
  int p = 0;
  rep (i, 0, n) if (abs(a[i]) > abs(a[p])) p = i;
  if (a[p] > 0) {
    rep (i, 0, n) if (a[i] < 0) ans.emplace_back(i, p); // 12
    rep (i, 1, n) ans.emplace_back(i, i - 1); // 19
  } else {
    rep (i, 0, n) if (a[i] > 0) ans.emplace_back(i, p); // 12
    for (int i = n - 1; i >= 1; i--) { // 19
      ans.emplace_back(i - 1, i);
    }
  }
  return print();
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