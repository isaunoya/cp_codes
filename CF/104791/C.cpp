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

using node = array<int, 3>;
node merge(const node &a, const node &b) {
  node c;
  c[0] = a[0] + b[0];
  c[1] = max(b[1], min(a[2] + b[0], a[1] + b[0]));
  c[2] = min(b[2], max(a[2] + b[0], b[1]));
  return c;
}

struct zkw {
  vector<node> t;
  int n, m, N;
  zkw(const vector<int> &x, int _n) {
    n = _n;
    m = x.size();
    N = 1;
    while (N < m) {
      N *= 2;
    }
    t.resize(N * 2);
    rep(i, n) t[i + N] = node{x[i], 1, n};
    rep(i, n, N) t[i + N] = node{0, 1, n};
    for (int i = N - 1; i >= 0; i--)
      t[i] = merge(t[i * 2], t[i * 2 + 1]);
  }
  void upd(int i, const int &v) {
    i += N;
    t[i] = node{v, 1, n};
    while (i >>= 1) {
      t[i] = merge(t[i * 2], t[i * 2 + 1]);
    }
  }
  node query(int l, int r) {
    node L = node{0, 1, n};
    node R = node{0, 1, n};
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        L = merge(L, t[l++]);
      }
      if (r & 1) {
        R = merge(t[--r], R);
      }
    }
    return merge(L, R);
  }
};

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  string s;
  cin >> s;
  vector<int> x(m, 0);
  vector<int> y(m, 0);

  rep(i, m) {
    if (s[i] == 'L')
      x[i] = -1;
    if (s[i] == 'R')
      x[i] = 1;
    if (s[i] == 'U')
      y[i] = -1;
    if (s[i] == 'D')
      y[i] = 1;
  }

  zkw X(x, n);
  zkw Y(y, n);

  while (k--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x, y, l, r;
      cin >> x >> y >> l >> r;
      --l;
      {
        auto [a, b, c] = X.query(l, r);
        x = min(c, max(x + a, b));
      }
      {
        auto [a, b, c] = Y.query(l, r);
        y = min(c, max(y + a, b));
      }

      cout << x << " " << y << "\n";
    } else {
      int i;
      char c;
      cin >> i >> c;
      --i;
      x[i] = y[i] = 0;
      s[i] = c;
      if (s[i] == 'L')
        x[i] = -1;
      if (s[i] == 'R')
        x[i] = 1;
      if (s[i] == 'U')
        y[i] = -1;
      if (s[i] == 'D')
        y[i] = 1;
      X.upd(i, x[i]);
      Y.upd(i, y[i]);
    }
  }
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

/*

1
5 5 4
RDRRD
1
5 3 1 5
1
5 1 4 5
2
1 L
1
2 3 1 5


*/