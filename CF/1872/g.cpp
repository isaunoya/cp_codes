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
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    cin >> x;
}
template <class T, class S> void read(pair<T, S> &v) {
  cin >> v.first >> v.second;
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

void solve() {
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) {
    cin >> a[i];
  }

  ll s = 1;
  bool ok = false;
  rep(i, n) {
    if (s < lnf / a[i]) {
      s *= a[i];
    } else {
      ok = true;
    }
  }
  if (ok) {
    int p1 = 0;
    int p2 = n - 1;
    while (p1 < n && a[p1] == 1) {
      p1++;
    }
    while (p2 >= 0 && a[p2] == 1) {
      p2--;
    }
    cout << p1 + 1 << " " << p2 + 1 << "\n";
    return;
  }
  vc<ll> prod(n + 1);
  prod[0] = 1;
  for (int i = 0; i < n; i++) {
    prod[i + 1] = prod[i] * a[i];
  }

  vi no1;
  rep(i, n) {
    if (a[i] == 1) {
      continue;
    }
    no1.pb(i);
  }

  vc<ll> sum(n + 1);
  rep(i, n) {
    sum[i + 1] = sum[i] + a[i];
  }

  int len = sz(no1);
  ll mxs = sum[n], L = n, R = n;
  rep(i, len) {
    rep(j, i, len) {
      int l = no1[i];
      int r = no1[j];
      ll tmp = prod[r + 1] / prod[l] + sum[l] + sum[n] - sum[r + 1];
      if (tmp > mxs) {
        mxs = tmp;
        L = l + 1;
        R = r + 1;
      }
    }
  }
  cout << L << " " << R << "\n";
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