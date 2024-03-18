#pragma GCC optimize("Ofast")
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
  int n, k;
  cin >> n >> k;
  vi a(n);
  vi b(k);
  rep(i, n) cin >> a[i];
  rep(i, k) cin >> b[i];

  auto check = [&](const ll &x) {
    vc<ll> A(n);
    rep(i, n) A[i] = 1ll * a[i] * x;
    for (int j = k - 1; j >= 0; j--) {
      ll t = (1 << j) - 1;
      auto check2 = [&](const ll &y) {
        ll ned = 0;
        rep(i, n) {
          if (A[i] <= y) continue;
          ned += (A[i] - y + t) >> j;
        }
        return ned <= b[j];
      };
      ll l = 0, r = 2e15;
      while (r - l > 1) {
        ll m = (l + r) / 2;
        if (check2(m)) {
          r = m;
        } else {
          l = m;
        }
      }
      ll c = b[j];
      rep(i, n) {
        if (A[i] <= r) continue;
        ll ned = (A[i] - r + t) >> j;
        A[i] -= ned << j;
        c -= ned;
      }
      pq<ll> q;
      rep(i, n) q.emplace(A[i]);
      while (c--) {
        auto w = q.top();
        q.pop();
        q.emplace(w - (1 << j));
      }
      rep(i, n) {
        A[i] = q.top();
        q.pop();
      }
    }
    
    rep(i, n) if (A[i] > 0) {
      return false;
    }
    return true;
  };
  check(4);
  ll s = accumulate(all(a), 0LL);
  ll r = 2e15 / s + 2;
  ll l = 0;
  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << "\n";
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