#include <bits/stdc++.h>
#include <unordered_map>
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

int n, q;
const int N = 1e5 + 5;
int a[N], f[N];
int d[N], cnt[N], id[N];
ll ans[N][400];

ll F(int x, int y) {
  if (x == 0 && y == 0) {
    return 0LL;
  }

  if (cnt[d[x]] >= 400) {
    return F(f[x], f[y]) + 1ll * a[x] * a[y];
  }

  if (ans[x][id[y]]) {
    return ans[x][id[y]];
  }
  return ans[x][id[y]] = F(f[x], f[y]) + 1ll * a[x] * a[y];
}
void solve() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  cnt[0] = 1;
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p;
    d[i] = d[p] + 1;
    id[i] = cnt[d[i]];
    cnt[d[i]] += 1;
    f[i] = p;
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << F(x, y) << "\n";
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