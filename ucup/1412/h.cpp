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

const double eps = 1e-7;
vector<double> gauss_jordan(vector<vector<double>> a) {
  int n = (int)a.size();
  for (int i = 0; i < n; i++) {
    int k = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(a[j][i]) > fabs(a[k][i])) {
        k = j;
      }
    }
    if (fabs(a[k][i]) < eps) {
      return {};
    }
    if (i != k) {
      swap(a[i], a[k]);
    }
    for (int j = 0; j < n; j++) {
      if (j == i) {
        continue;
      }
      double p = a[j][i] / a[i][i];
      for (int k = i; k <= n; k++) {
        a[j][k] -= p * a[i][k];
      }
    }
  }
  vector<double> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = a[i].back() / a[i][i];
  }
  return res;
}

void solve() {
  int n;
  cin >> n;
  vc<vi> e(n, vi(n));
  rep(i, n) rep(j, n) cin >> e[i][j];
  auto eval = [&](vc<double> x) {
    double ans = 0;
    rep(i, n) rep(j, i + 1, n) ans += x[i] * x[j] * e[i][j];
    return ans;
  };
  double ans = 0.0;
  rep(s, (1 << n) - 1) {
    vc<double> x(n, 0);
    vi id;
    int cnt = 0;
    rep(i, n) if (~s >> i & 1) {
      id.pb(i);
      cnt++;
    }
    vector<vector<double>> a;
    a.pb(vector<double>(cnt + 1, 1));
    vector<double> first(cnt);
    rep(i, cnt) first[i] = e[id[0]][id[i]];
    rep(i, 1, cnt) {
      vector<double> now(cnt);
      rep(j, cnt) now[j] = e[id[i]][id[j]];
      vector<double> push(cnt + 1, 0);
      rep(j, cnt) push[j] = now[j] - first[j];
      a.pb(push);
    }
    // debug(a.size(), a[0].size());
    auto y = gauss_jordan(a);
    if (y.size() < cnt || *min_element(all(y)) < 0.) continue;
    rep(i, cnt) x[id[i]] = y[i];
    cmax(ans, eval(x));
    // debug(x);
    // debug(eval(x));
  }

  cout << fixed << setprecision(10) << ans << "\n";
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