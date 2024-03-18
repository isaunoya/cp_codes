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
  int k;
  cin >> k;
  if (k == 1) {
    cout << "2 1" << "\n";
    cout << "1 2" << "\n";
    return;
  }
  if (k == 2) {
    cout << "4 4" << "\n";
    cout << "1 2" << "\n";
    cout << "3 1" << "\n";
    cout << "2 3" << "\n";
    cout << "3 4" << "\n";
    return;
  }
  if (k <= 20) {
    cout << k << " " << k << "\n";
    rep(i, 1, k) cout << i << " " << i + 1 << "\n";
    cout << k << " " << 1 << "\n";
    return;
  }
  for (int a = 2; a <= 17; a++) {
    for (int b = 3; b <= 20 - a; b++) {
      int cnt = b * (b - 1) / 2 - 1 + a - 1 + 2 * (b - 1);
      if (cnt == k) {
        cout << a + b << " " << b * (b - 1) / 2 + a + 1 << "\n";
        rep(i, 1, a) cout << i << " " << i + 1 << "\n";
        for (int i = 1; i <= b; i++) {
          for (int j = i + 1; j <= b; j++) {
            cout << i + a << " " << j + a << "\n";
          }
        }
        cout << 1 << " " << a + 1 << "\n";
        cout << a << " " << a + 2 << "\n";
        return;
      }
    }
  }
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