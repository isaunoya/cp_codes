#include <bits/stdc++.h>
#include <iomanip>
#include <valarray>
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
using ar = valarray<double>;
double dot(const ar &x, const ar &y) {
  double res = 0;
  rep(i, sz(x)) res += 1. * x[i] * y[i];
  return res;
}
const double eps = 1e-9;
void solve() {
  int n, m;
  cin >> n >> m;
  vc<ar> v(m, ar(n));
  rep(i, m) for (auto &d : v[i]) {
    string s;
    cin >> s;
    d = stod(s);
  }
  uniform_real_distribution<double> rnd(-10, 10);
  rep(i, m, n + 1) {
    ar o(n);
    for (auto vv : v)
      o += vv;
    o /= i;
    auto vv = v;
    for (auto &vvv : vv)
      vvv -= o;
    rep(k, i) rep(j, k) {
      auto x = (vv[j]) * dot(vv[k], vv[j]);
      vv[k] -= x;
      if (dot(vv[k], vv[k]) < eps)
        continue;
      auto t = dot(vv[k], vv[k]);
      vv[k] /= sqrt(t);
    }
    ar d(n);
    for (auto &dd : d)
      dd = rnd(rng);
    // generate(all(d),rnd(rng));
    rep(j, i) {
      auto x = (vv[j]) * dot(d, vv[j]);
      d -= x;
      double t = dot(d, d);
      d /= sqrt(t);
    }
    double l = sqrt(1. - dot(v[0] - o, v[0] - o));
    v.pb(o + d * l);
  }
  static int cas = 0;
  cout << "Case #" << ++cas << ": " << n + 1 - m << "\n";
  cout << fixed << setprecision(10);
  rep(i, m, n + 1) {
    for (int j = 0; j < n; j++)
      cout << v[i][j] << " \n"[j + 1 == n];
  }
  rep(i,n+1){
    rep(j,n+1){
      if(i==j)continue;
      if(abs(dot(v[i]-v[j],v[i]-v[j])-1)>eps){
        debug(i,j,dot(v[i]-v[j],v[i]-v[j]));
      }
    }
  }
}

/*
1
5 1
0 0 0 0 0
*/

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