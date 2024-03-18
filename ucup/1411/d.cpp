#include <algorithm>
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

const int N = 262145;
int c[N];
ll s[N];
vi b;
void upd(int x, const int &v1, const int &v2) {
  while (x < N) {
    c[x] += v1;
    s[x] += v2;
    x += x & -x;
  }
}
ll query(int x) {
  int r = 0;
  ll res = 0;
  for (int i = 17; i >= 0; i--) {
    if (c[r | (1 << i)] < x) {
      x -= c[r | (1 << i)];
      res += s[r | (1 << i)];
      r |= 1 << i;
    }
  }
  res += 1ll * x * b[r];
  return res;
}

// int c2[N];
// ll s2[N];
// void upd2(int x, int v) {
//   while (x < N) {
//     c2[x] += 1;
//     s2[x] += v;
//     x += x & -x;
//   }
// }
// ll query2(int x) {
//   int r = 0;
//   ll res = 0;
//   for (int i = 17; i >= 0; i--) {
//     if (c2[r | (1 << i)] < x) {
//       x -= c2[r | (1 << i)];
//       res += s2[r | (1 << i)];
//       r |= 1 << i;
//     }
//   }
//   res += 1ll * x * b[r];
//   return res;
// }

void clear() {
  memset(c, 0, sizeof c);
  memset(s, 0, sizeof s);
  // memset(c2, 0, sizeof c2);
  // memset(s2, 0, sizeof s2);
}

void solve() {
  clear();
  int n, m;
  cin >> n >> m;
  vi a(n);
  rep(i, n) cin >> a[i];
  b = a;
  sort(all(b));
  b.resize(unique(all(b)) - b.begin());
  rep(i, n) { a[i] = lower_bound(all(b), a[i]) - b.begin(); }
  vc<ll> t(n);
  rep(i, m) {
    int r, w;
    cin >> r >> w;
    --r;
    t[r] += w;
  }
  vc<ll> T(n + 1);
  for (int i = n - 1; i >= 0; i--) {
    T[i] = T[i + 1] + t[i];
  }
  int p = n - 1;
  // p2 = n - 1;
  auto getans1 = [&](int x, int k) {
    if (n - 1 - x < k) {
      return lnf;
    }
    while (p > x)
      upd(a[p] + 1, 1, b[a[p]]), p--;
    while (p < x)
      p++, upd(a[p] + 1, -1, -b[a[p]]);
    return -T[x] + query(k) + b[a[x]];
  };
  // auto getans2 = [&](int x, int k) {
  //   while (p2 > x)
  //     upd2(a[p2] + 1, b[a[p2]]), p2--;
  //   return -T[x] + query2(k);
  // };
  vc<ll> ans(n + 1);
  auto get = [&](auto &self, int l, int r, int ql, int qr) {
    if (l > r) {
      return;
    }
    int m = (l + r) / 2;
    ll &res = ans[m];
    res = getans1(ql, m);
    int qm = ql;
    for (int i = ql; i <= qr; i++) {
      // debug(i, m - 1, getans1(i, m - 1));
      ll cur = getans1(i, m - 1);
      if (cur < res) {
        res = cur;
        qm = i;
      }
    }
    self(self, l, m - 1, qm, qr);
    self(self, m + 1, r, ql, qm);
  };
  get(get, 1, n, 0, n - 1);
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  // vi pos(n);
  // pos[0] = 0;
  // for (int i = 1; i < n; i++) {
  //   pos[i] = i;
  //   if (a[pos[i - 1]] > a[pos[i]]) {
  //     pos[i] = i;
  //   } else {
  //     pos[i] = pos[i - 1];
  //   }
  // }
  // pos.resize(unique(all(pos)) - pos.begin());
  // debug(pos);
  // int w = pos.size() - 1;
  // for (int k = 1; k <= n; k++) {
  //   while (w - 1 >= 0 && n - pos[w] < k)
  //     w -= 1;
  //   while (w - 1 >= 0 && getans1(pos[w - 1], k - 1) + b[a[pos[w - 1]]] <=
  //                            getans2(pos[w], k - 1) + b[a[pos[w]]]) {
  //     w -= 1;
  //   }
  //   debug(pos[w], getans2(pos[w], k - 1) + b[a[pos[w]]]);
  //   cout << getans2(pos[w], k - 1) + b[a[pos[w]]] << " \n"[k == n];
  // }
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
5 5
7 6 9 4 3
5 0
5 1
2 8
1 0
5 2
*/