#include <bits/stdc++.h>
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
  int n, m;
  cin >> n >> m;
  vc<array<int, 3>> a(n);
  rep(i, n) {
    rep(j, 3) {
      cin >> a[i][j];
    }
    a[i][0]--;
  }
  vc<array<int, 4>> b(m);

  ll ans = lnf;
  rep(i, m) {
    rep(j, 4) {
      cin >> b[i][j];
    }
    b[i][0]--;
  }

  rep(s, 1 << m) {
    ll cost = 0;

    vc<ll> A(100, 0);
    rep(i, m) {
      if (s >> i & 1) {
        // debug(s, i, b[i]);
        rep(j, b[i][0], b[i][1]) {
          A[j] += b[i][2];
        }
        cost += b[i][3];
      }
    }
    // debug(A);
    bool ok = true;
    rep(i, n) {
      rep(j, a[i][0], a[i][1]) {
        if (A[j] < a[i][2]) {
          ok = false;
          break;
        }
      }
    }

    if (ok) {
      cmin(ans, cost);
    }
  }

  cout << ans << "\n";
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