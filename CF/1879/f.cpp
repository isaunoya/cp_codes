#include <bits/stdc++.h>
#include <cmath>
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

const int V = 2e5;
void solve() {
  int n;
  cin >> n;
  vi h(n), a(n);
  rep(i, n) cin >> h[i];
  rep(i, n) cin >> a[i];

  map<pii, int> id;
  rep(i, n) id[{h[i], a[i]}] = i;
  vc<array<pii, 2>> f(V + 1);
  rep(i, n) {
    auto v = make_pair(h[i], a[i]);
    for (auto &y : f[a[i]]) {
      if (v > y) {
        swap(v, y);
      }
    }
  }
  for (int i = V - 1; i >= 0; i--) {
    for (auto v : f[i + 1]) {
      for (auto &y : f[i]) {
        if (v > y) {
          swap(v, y);
        }
      }
    }
  }

  vc<ll> ans(n);
  rep(x, 1, V + 1) {
    ll mx = 0;
    int l = 0;
    for (int i = 1; i <= V; i += x) {
      ll res = 1ll * (i + x - 1) / x * f[i][0].fi;
      if (res > mx) {
        mx = res;
        l = i;
      }
    }
    auto v = f[l][0];
    ll sec = 0;
    for (int i = 1; i <= V; i += x) {
      ll res = 1ll * (i + x - 1) / x * f[i][f[i][0] == v].fi;
      if (res > sec) {
        sec = res;
      }
    }
    if (sec < mx) {
      cmax(ans[id[v]], mx - sec);
    }
  }

  rep(i, n) cout << ans[i] << " \n"[i + 1 == n];
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