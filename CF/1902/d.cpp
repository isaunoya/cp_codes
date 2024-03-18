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
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  map<pii, int> L, R, X;

  vi x(n + 1), y(n + 1);
  rep(i, n) {
    x[i + 1] = x[i];
    y[i + 1] = y[i];
    if (s[i] == 'R') x[i + 1] += 1;
    if (s[i] == 'L') x[i + 1] -= 1;
    if (s[i] == 'U') y[i + 1] += 1;
    if (s[i] == 'D') y[i + 1] -= 1;
  }
  rep(i, n + 1) R[pii(x[i], y[i])] = i;
  for (int i = n; i >= 0; i--) L[pii(x[i], y[i])] = i;

  vi ans(q);
  vc<vc<array<int, 4>>> Q(n + 1);
  // s_{l-1} + (s_{r}-s_{m}) = x
  // m \in [l,r]
  // s_{m} = s_{l-1} + s_{r} - x
  rep(i, q) {
    int l, r, xx, yy;
    cin >> xx >> yy >> l >> r;
    ans[i] |= (L.count(pii(xx, yy)) && L[pii(xx, yy)] < l);
    ans[i] |= (R.count(pii(xx, yy)) && R[pii(xx, yy)] >= r);
    xx = x[l - 1] + x[r] - xx;
    yy = y[l - 1] + y[r] - yy;
    Q[r].pb(array<int, 4>{i, l, xx, yy});
  }

  rep(r, n + 1) {
    X[pii(x[r], y[r])] = r;
    for (auto [i, l, xx, yy] : Q[r]) {
      // debug(i, l, xx, yy);
      ans[i] |= X[pii(xx, yy)] >= l;
    }
  }

  rep(i, q) if (ans[i]) cout << "YES\n"; else cout << "NO\n";
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