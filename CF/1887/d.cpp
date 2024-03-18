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

void solve() {
  int n;
  cin >> n;
  vi a(n), p(n);
  rep(i, n) cin >> a[i], --a[i], p[a[i]] = i;
  int q;
  cin >> q;
  vc<vc<pii>> qq(n);
  rep(i, q) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    qq[l].pb(r, i);
  }
  vi t(n * 2);
  auto add = [&](int x, const int &v) {
    if (x >= n)
      return;
    x += n;
    t[x] += v;
    while (x >>= 1)
      t[x] += v;
  };
  auto query = [&](int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        res += t[l++];
      if (r & 1)
        res += t[--r];
    }
    return res;
  };
  set<int> s = {-1, n};
  vc<vc<pii>> aa(n + 1);
  vi L(n), R(n), rr(n);
  for (int i = n - 1; i >= 0; i--) {
    int pos = p[i];
    int l = *prev(s.lower_bound(pos));
    int r = *s.upper_bound(pos);
    s.emplace(pos);
    L[pos] = l;
    R[pos] = r;
  }
  s = {-1, n};
  rep(i, n) {
    int pos = p[i];
    if (R[pos] < n) {
      rr[pos] = *s.lower_bound(R[pos]);
    }
    s.emplace(pos);
  }
  rep(i, n) {
    int l = L[i], r = R[i], r2 = rr[i];
    if (r >= n)
      continue;
    aa[l + 1].pb(r, 1);
    aa[l + 1].pb(r2, -1);
    aa[i + 1].pb(r, -1);
    aa[i + 1].pb(r2, 1);
  }
  vi ans(q);
  rep(i, n) {
    for (auto [x, y] : aa[i])
      add(x, y);
    for (auto [r, j] : qq[i])
      ans[j] = query(0, r + 1);
  }
  rep(i, q) if (ans[i]) cout << "YES\n";
  else cout << "NO\n";
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