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

int n, m, R, q, P;
const int N = 5005;
const int M = 2500 + 2;
double f[N][N], g[N][N];
// f[i][j], 选择了 i 个技能，成功发动了 j 个的概率
// g[i][j]，选择了 i 个技能，成功提前发动了 j 个的概率
// 至少发动 k 个技能，至多 k-1 个技能提前发动的概率

void solve() {
  cin >> n >> m >> R >> q >> P;
  double p = P / 100.;
  f[0][0] = 1.;
  for (int i = 1; i <= n; i++) {
    f[i][0] = f[i - 1][0] * (1 - p);
    for (int j = 1; j <= i; j++) {
      f[i][j] = p * f[i - 1][j - 1] + (1 - p) * f[i - 1][j];
    }
  }
  vc<double> prob;
  rep(i, n) {
    int l, r;
    cin >> l >> r;
    if (r < R)
      prob.pb(1.);
    else if (l < R) {
      int len = r - R;
      prob.pb(1. - 1. * len / (r - l));
    } else {
      prob.pb(0);
    }
  }
  prob.pb(0);
  sort(all(prob));
  debug(prob);
  g[0][0] = 1.;
  for (int i = 1; i <= n; i++) {
    g[i][0] = g[i - 1][0] * (1 - p * prob[i]);
    for (int j = 1; j <= i; j++)
      g[i][j] = p * prob[i] * g[i - 1][j - 1] + (1 - p * prob[i]) * g[i - 1][j];
    // for(int j=0;j<=i;j++)cout<<g[i][j]<<" \n"[j==i];
  }
  cout << fixed << setprecision(10);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      f[i][j] += f[i][j - 1];
  for (int i = 1; i <= n; i++)
    for (int j = n - 1; j >= 0; j--)
      g[i][j] += g[i][j + 1];
  while (q--) {
    int k;
    cin >> k;
    double ans = 0;
    for (int l = k; l <= n; l++) {
      cmax(ans, 1 - f[l][k - 1] - g[l][k]);
    }
    cout << ans << "\n";
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