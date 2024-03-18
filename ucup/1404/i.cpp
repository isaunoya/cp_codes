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

const int N = 5e5 + 5;
int pos[N];
void solve() {
  int n, m;
  cin >> n >> m;
  vi a(n);
  rep(i, n) cin >> a[i];
  rep(i, n) pos[a[i]] = -1;
  vector<int> t(n * 2);
  auto upd = [&](int x, int v) {
    x += n;
    while (x) {
      t[x] += v;
      x /= 2;
    }
    return;
  };
  auto query = [&](int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        ans += t[l++];
      if (r & 1)
        ans += t[--r];
    }
    return ans;
  };
  vc<vc<pii>> querys(n);
  int cnt = 0;
  rep(i, n) {
    int l = pos[a[i]] + 1;
    int r = i - 1;
    if (l <= r) {
      querys[r].pb(l, -a[i]);
    }
    if (pos[a[i]] == -1)
      cnt++;
    pos[a[i]] = i;
  }
  int mex = 1;
  while (pos[mex] != -1)
    mex++;
  rep(i, n) {
    int l = pos[a[i]] + 1;
    int r = n - 1;
    if (l <= r) {
      querys[r].pb(l, -a[i]);
    }
  }
  rep(i, n) pos[a[i]] = -1;
  int ans = cnt - mex;
  // debug(cnt,mex);
  rep(i, n) {
    if (pos[a[i]] != -1)
      upd(pos[a[i]], -1);
    pos[a[i]] = i, upd(i, 1);
    for (auto [j, v] : querys[i])
      cmax(ans, query(j, i + 1) + v);
  }
  cout << ans << "\n";
  rep(i, n) pos[a[i]] = -1;
}

int main() {
  memset(pos, -1, sizeof pos);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}