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
  ll k;
  cin >> n >> k;
  vc<ll> a(n);
  rep(i, n) cin >> a[i];
  int cntk = 0;
  rep(i, n) if (a[i] == k) cntk += 1;
  if (0 < cntk && cntk < n) {
    cout << -1 << "\n";
    return;
  }
  int cnt0 = 0, cnt1 = 0;
  rep(i, n) {
    if (a[i] < k) {
      cnt0++;
    }
    if (a[i] > k) {
      cnt1++;
    }
  }
  if (cnt0 && cnt1) {
    cout << -1 << "\n";
    return;
  }

  // if all x<k, p-k<0
  // if all x>k, p-k>0

  // x+tk=(t+1)p
  // x-k=(t+1)(p-k)
  // (p-k)|(x-k)

  ll g = 0;
  rep(i, n) g = gcd(g, a[i] - k);
  if (g == 0) {
    cout << 0 << "\n";
    return;
  }
  ll res = 0;
  rep(i, n) res += abs(a[i] - k) / g - 1;
  cout << res << "\n";
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

/*

1
5 616753575719
321037808624 222034505841 214063039282 441536506916 464097941819

*/