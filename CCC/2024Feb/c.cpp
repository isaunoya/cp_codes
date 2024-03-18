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

const int N = 3e5 + 5;
int n, a[N], b[N];
void solve() {
  cin >> n;
  rep(i, n) cin >> a[i];
  rep(i, n) cin >> b[i];
  vector<tuple<int, int, int>> seg;
  for (int l = 0, r; l < n; l = r) {
    r = l;
    while (r < n && b[r] == b[l]) {
      r++;
    }
    seg.emplace_back(l, r - 1, b[l]);
  }

  vi pos;
  int p = 0;
  for (auto [l, r, v] : seg) {
    while (p < n && a[p] != v) {
      p++;
    }
    pos.emplace_back(p);
  }
  if (p == n) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  vc<tuple<int, int, int>> ans;
  int m = (int)seg.size();
  for (int i = m - 1; i >= 0; i--) {
    auto [l, r, v] = seg[i];
    int p = pos[i];
    if (p <= l) {
      if (p != r)
        ans.emplace_back(1, p, r);
      pos[i] = l;
    } else if (l < p && p < r) { // len > 2
      ans.emplace_back(1, p, r);
    } // else p >= r
  }
  for (int i = 0; i < m; i++) {
    auto [l, r, v] = seg[i];
    if (l != pos[i])
      ans.emplace_back(0, l, pos[i]);
  }
  cout << (int)ans.size() << "\n";
  for (auto [op, l, r] : ans) {
    if (op == 0) {
      cout << "L";
    } else {
      cout << "R";
    }
    cout << " " << l << " " << r << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}