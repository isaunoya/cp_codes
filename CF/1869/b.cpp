#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
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

template <class... T> void read() {}
template <class T> void read(T &x) { cin >> x; }
template <class T, class S> void read(pair<T, S> &v) {
  read(v.first, v.second);
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}


void solve() {
  int n, k, a, b;
  cin >> n >> k >> a >> b;
  vc<pii> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].first >> p[i].second;
  }

  --a;
  --b;
  ll d1 = lnf;
  ll d2 = lnf;
  for (int i = 0; i < k; i++) {
    ll tmp = 0;
    if (i != a) {
      tmp += abs(p[i].first - p[a].first);
      tmp += abs(p[i].second - p[a].second);
      cmin(d1, tmp);
      tmp = 0;
    }
    if (i != b) {
      tmp += abs(p[i].first - p[b].first);
      tmp += abs(p[i].second - p[b].second);
      cmin(d2, tmp); 
    }
  }
  if (a < k) {
    d1 = 0;
  }
  if (b < k) {
    d2 = 0;
  }
  ll ans = d1 + d2;
  ll tmp = 0;
  tmp += abs(p[a].first - p[b].first);
  tmp += abs(p[a].second - p[b].second);
  cout << min(ans, tmp) << "\n";

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