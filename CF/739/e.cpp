#include <algorithm>
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
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class S> void read(pair<T, S> &v) {
  cin >> v.first >> v.second;
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

void solve() {

  int n, a, b;
  read(n, a, b);
  vc<double> p(n), q(n);
  read(p, q);
  vi per(n);
  iota(all(per), 0);
  shuffle(all(per), rng);

  vc<double> P(n), Q(n);
  rep(i, n) {
    P[i] = p[per[i]];
    Q[i] = q[per[i]];
  }
  p.swap(P);
  q.swap(Q);

  vc<vc<double>> dp(a + 1, vc<double>(b + 1, 0.00));
  rep (i, n) {
    double pp = p[i];
    double qq = q[i];
    double pq = pp + qq - pp * qq;
    int na = a * i / n;
    int nb = b * i / n;
    int la = na - 50;
    int ra = na + 50;
    int lb = nb - 50;
    int rb = nb + 50;
    cmax(la, 0);
    cmax(lb, 0);
    cmin(ra, i + 1);
    cmin(rb, i + 1);
    for (int x = ra - 1; x >= la; x--) {
      for (int y = rb - 1; y >= lb; y--) {
        if (x + 1 <= a && y + 0 <= b)
          cmax(dp[x + 1][y + 0], dp[x][y] + pp);
        if (x + 0 <= a && y + 1 <= b)
          cmax(dp[x + 0][y + 1], dp[x][y] + qq);
        if (x + 1 <= a && y + 1 <= b)
          cmax(dp[x + 1][y + 1], dp[x][y] + pq);
      }
    }
  }

  cout << dp[a][b] << "\n";
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