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

void solve() {
  int n, q;
  cin >> n >> q;
  vc<ll> t(n * 2);
  auto upd = [&](int x, int v) {
    t[x += n] = v;
    while (x >>= 1) {
      t[x] = t[x * 2] + t[x * 2 + 1];
    }
  };

  auto query = [&](int l, int r) {
    ll res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        res += t[l++];
      }
      if (r & 1) {
        res += t[--r];
      }
    }
    return res;
  };

  vi a(n);
  rep(i, n) { cin >> a[i]; }
  vi o(q);
  vc<tuple<int, int, int>> que;
  vi res(q, -1);
  rep(i, q) {
    int op;
    cin >> op;
    o[i] = op;
    if (op == 1) {
      int j, x;
      cin >> j >> x;
      --j;
      que.emplace_back(j, x, 0);
    } else {
      int l, r, k;
      cin >> l >> r >> k;
      --l;
      que.emplace_back(l, r, k);
      res[i] = 1;
    }
  }
  vi b = a;
  rep(i, q) if (o[i] == 1) b.emplace_back(get<1>(que[i]));
  sort(all(b));
  b.resize(unique(all(b)) - b.begin());
  rep(i, n) a[i] = lower_bound(all(b), a[i]) - b.begin();
  rep(i, q) if (o[i] == 1) {
    int &x = get<1>(que[i]);
    x = lower_bound(all(b), x) - b.begin();
  }
  int m = b.size();
  vi F(m);
  rep(w, 40) {
    rep(i, m) F[i] = rng() % inf;
    rep(i, n) upd(i, F[a[i]]);
    rep(i, q) {
      if (o[i] == 1) {
        auto [j, x, tmp] = que[i];
        upd(j, F[x]);
      } else {
        auto [l, r, k] = que[i];
        res[i] &= (query(l, r) % k == 0);
      }
    }
  }
  rep(i, q) {
    if (res[i] == -1)
      continue;
    else {
      cout << (res[i] ? "YES" : "NO") << "\n";
    }
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