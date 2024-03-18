#include <bits/stdc++.h>

#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

template <typename T> struct Fenwick {
  int n;
  std::vector<T> a;

  Fenwick(int n = 0) { init(n); }

  void init(int n) {
    this->n = n;
    a.assign(n, T());
  }

  void add(int x, T v) {
    for (int i = x + 1; i <= n; i += i & -i) {
      a[i - 1] += v;
    }
  }

  T sum(int x) {
    auto ans = T();
    for (int i = x; i > 0; i -= i & -i) {
      ans += a[i - 1];
    }
    return ans;
  }

  T rangeSum(int l, int r) { return sum(r) - sum(l); }

  int kth(T k) {
    int x = 0;
    for (int i = 1 << std::__lg(n); i; i /= 2) {
      if (x + i <= n && k >= a[x + i - 1]) {
        x += i;
        k -= a[x - 1];
      }
    }
    return x;
  }
};

void solve() {
  int n, Q;
  cin >> n >> Q;
  vc<vi> v(n);
  vi a(n);
  rep(i, 0, n) cin >> a[i], --a[i], v[a[i]].pb(i);
  vc<vc<pii>> q(n);
  rep(i, 0, Q) {
    int l, r;
    cin >> l >> r;
    --l;
    q[l].pb(r, i);
  }
  vi t(n * 2, -1);
  auto upd = [&](int x, int v) {
    t[x += n] = v;
    while (x >>= 1)
      t[x] = max(t[x * 2], t[x * 2 + 1]);
  };
  auto query = [&](int l, int r) {
    int ans = -1;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        cmax(ans, t[l++]);
      if (r & 1)
        cmax(ans, t[--r]);
    }
    return ans;
  };
  vi sum(n + 1);
  rep(i, 0, n) sum[i + 1] = sum[i] + sz(v[i]);
  vc<pii> tmp;
  vi ans(Q);
  rp(i, n) {
    rep(j, 1, sz(v[i])) {
      int lst = v[i][j - 1], now = v[i][j];
      int mx = query(lst + 1, now);
      tmp.pb(mx, i);
    }
    for (auto j : v[i])
      upd(j, i);
  }
  sort(all(tmp));
  int i = 0;
  Fenwick<int> f(n);
  rp(l, n) {
    while (i < sz(tmp) && tmp[i].first < l)
      f.add(tmp[i].second, 1), i += 1;
    for (auto [r, id] : q[l])
      ans[id] = sum[r] - sum[l] - f.rangeSum(l, r);
  }
  rp(i, Q) cout << ans[i] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}