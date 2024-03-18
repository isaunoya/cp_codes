#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
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

void solve() {
  int n, c;
  cin >> n >> c;
  vi dif(n);
  string s;
  cin >> s;
  int cnt = 0;
  rep(i, n) {
    if (s[i] == s[n - 1 - i]) dif[i] = 0;
    else dif[i] = 1, cnt++;
  }
  cnt /= 2;
  vi h(n);
  read(h);

  vi p(n);
  ll t = 0;
  int w = 0;
  int L = 1, R = 0;
  auto add = [&](int x) {
    if (!dif[x]) {
      return;
    }
    int y = min(x, n - 1 - x);
    p[y] += 1;
    if (p[y] == 1) {
      t += h[x];
      w += 1;
    } else {
      t -= h[n - 1 - x];
      t += min(h[x], h[n - 1 - x]);
    }
  };

  auto del = [&](int x) {
    if (!dif[x]) {
      return;
    }
    int y = min(x, n - 1 - x);
    p[y] -= 1;
    if (p[y] == 0) {
      t -= h[x];
      w -= 1;
    } else {
      t -= min(h[x], h[n - 1 - x]);
      t += h[n - 1 - x];
    }
  };


  auto calc = [&](int l, int r) {
    while (L > l) {
      add(--L);
    }
    while (R < r) {
      add(++R);
    }
    while (L < l) {
      del(L++);
    }
    while (R > r) {
      del(R--);
    }
  };

  vc<ll> ans(n, lnf);
  auto solve = [&](auto self, int l, int r, int a, int b) -> void {
    if (l > r) {
      return;
    }
    debug(l, r, a, b);
    int m = (l + r) / 2;
    int p = max(m, a);
    calc(m, p);
    while (p + 1 < n && w < cnt) {
      p += 1;
      calc(m, p);
    }
    if (w < cnt) {
      self(self, l, m - 1, a, p);
      return;
    }
    ll res = t + 1ll * (p - m) * c;
    for (int i = p; i <= b; i++) {
      calc(m, i);
      if (res > t + 1ll * (i - m) * c) {
        res = t + 1ll * (i - m) * c;
        p = i;
      }
    }
    cmin(ans[m], res);

    self(self, l, m - 1, a, p);
    self(self, m + 1, r, p, b);
  };

  t = 0, w = 0, L = 1, R = 0;
  rep(i, n) p[i] = 0;
  solve(solve, 0, n - 1, 0, n - 1);
  reverse(all(ans));
  reverse(all(h));
  t = 0, w = 0, L = 1, R = 0;
  rep(i, n) p[i] = 0;
  solve(solve, 0, n - 1, 0, n - 1);
  reverse(all(ans));
  reverse(all(h));


  ll mn = lnf;
  for (int i = 0; i < n; i++) {
    cmin(ans[i], mn + 1ll * i * c);
    cmin(mn, ans[i] - 1ll * i * c);
  }
  reverse(all(ans));
  mn = lnf;
  for (int i = 0; i < n; i++) {
    cmin(ans[i], mn + 1ll * i * c);
    cmin(mn, ans[i] - 1ll * i * c);
  }
  reverse(all(ans));

  for (auto x : ans) {
    cout << x << " ";
  }
  cout << "\n";
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