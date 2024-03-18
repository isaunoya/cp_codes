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
template <class T, class S> void read(pair<T, S> &v) {
  read(v.first, v.second);
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

const int N = 1e5 + 5;
int n, l, k;
int a[N];
int dp[10][N];
struct st {
int t[N * 4], mn[N * 4];
st() {
  memset(mn, 0x3f, sizeof mn);
}
void ps(int p, int v) {
  t[p] += v;
  mn[p] += v;
}
void psd(int p) {
  if (t[p]) {
    ps(p * 2, t[p]);
    ps(p * 2 + 1, t[p]);
    t[p] = 0;
  }
}
void pu(int p) {
  mn[p] = min(mn[p * 2], mn[p * 2 + 1]);
}

void update(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    ps(p, 1);
    return;
  }
  psd(p);
  int m = (l + r) / 2;
  if (ql <= m) {
    update(ql, qr, l, m, p * 2);
  }
  if (qr > m) {
    update(ql, qr, m + 1, r, p * 2 + 1);
  }
  pu(p);
}

void upd(int x, int l, int r, int p, int v) {
  if (l == r) {
    cmin(mn[p], v);
    return;
  }
  psd(p);
  int m = (l + r) / 2;
  if (x <= m) {
    upd(x, l, m, p * 2, v);
  } else {
    upd(x, m + 1, r, p * 2 + 1, v);
  }
  pu(p);
}

int query(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) {
    return mn[p];
  }
  psd(p);
  int m = (l + r) / 2;
  int mn = inf;
  if (ql <= m) {
    cmin(mn, query(ql, qr, l, m, p * 2));
  }
  if (qr > m) {
    cmin(mn, query(ql, qr, m + 1, r, p * 2 + 1));
  }
  return mn;
}
} t[10];

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> l >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<int> b;
  for (int i = 1; i <= n; i++) {
    b.emplace_back(a[i]);
  }
  sort(all(b));

  b.resize(unique(all(b)) - b.begin());
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(all(b), a[i]) - b.begin() + 1;
  }
  int res = 0;
  for (int i = 1; i < l; i++) {
    if (a[i] >= a[l]) {
      res += 1;
    }
  }

  memset(dp, 0x3f, sizeof dp);
  dp[0][l] = 0;
  k -= 1;
  for (int i = 1; i <= k; i++) {
    for (int j = l; j <= n; j++) {
      if (a[j] > 1)
        dp[i][j] = t[i - 1].query(1, a[j] - 1, 1, n, 1);
      t[i - 1].upd(a[j], 1, n, 1, dp[i - 1][j]);
      if (a[j] > 1)
        t[i - 1].update(1, a[j] - 1, 1, n, 1);
    }
  }

  int ans = inf;
  Fenwick<int> f(n + 1);
  for (int j = n; j >= l; j--) {
    cmin(ans, dp[k][j] + f.rangeSum(a[j] + 1, n + 1));
    f.add(a[j], 1);
  }

  if (ans >= inf) {
    cout << -1 << "\n";
  } else {
    cout << ans + res << "\n";
  }
  return 0;
}