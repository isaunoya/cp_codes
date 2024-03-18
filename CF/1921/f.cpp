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

const int N = 1e5 + 53;
int n, q, a[N];
ll s[N][320], s2[N][320];
void solve() {
  cin >> n >> q;
  rep(i, n) cin >> a[i];
  rep(k, 1, 320) for (int i = n - 1; i >= 0; i--) {
    s[i][k] = a[i];
    if (i + k < n)
      s[i][k] += s[i + k][k];
  }
  rep(k, 1, 320) for (int i = n - 1; i >= 0; i--) {
    s2[i][k] = s[i][k];
    if (i + k < n)
      s2[i][k] += s2[i + k][k];
  }
  while (q--) {
    int st, d, k;
    cin >> st >> d >> k;
    st--;
    if (d >= 320) {
      ll res = 0;
      rep(i, k) res += 1ll * a[st + i * d] * (i + 1);
      cout << res << " ";
    } else {
      ll res = s2[st][d] - s2[st + k * d][d];
      res -= k * s[st + k * d][d];
      cout << res << " ";
    }
  }
  cout << "\n";

  rep(k, 1, 320) rep(i, n) s[i][k] = s2[i][k] = 0;
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