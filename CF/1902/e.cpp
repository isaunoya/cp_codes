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

const int N = 2e6 + 5;
int ch[N][26];
int sz[N];
int cnt = 1;
void solve() {
  int n;
  cin >> n;
  ll ans = 0;
  ll sum = 0;
  vc<string> s(n);
  rep(i, n) {
    cin >> s[i];
    sum += sz(s[i]);
    int p = 1;
    for (auto c : s[i]) {
      int x = c - 'a';
      if (!ch[p][x])
        ch[p][x] = ++cnt;
      p = ch[p][x];
      sz[p] += 1;
    }
  }
  ans = sum * n * 2;
  debug(ans);
  rep(i, n) {
    reverse(all(s[i]));
    int p = 1;
    for (auto c : s[i]) {
      int x = c - 'a';
      if (!ch[p][x])
        break;
      p = ch[p][x];
      ans -= sz[p] * 2;
    }
  }

  cout << ans << "\n";
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