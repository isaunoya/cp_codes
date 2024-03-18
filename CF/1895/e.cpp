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
  int n;
  cin >> n;
  vc<pii> a(n);
  rep(i, n) cin >> a[i].fi; // atk
  rep(i, n) cin >> a[i].se; // def

  int m;
  cin >> m;
  vc<pii> b(m);
  rep(i, m) cin >> b[i].fi;
  rep(i, m) cin >> b[i].se;

  sort(all(a));
  sort(all(b));

  vc<pii> sa(n);
  vc<pii> sb(m);

  for (int i = n - 1; i >= 0; i--) {
    sa[i] = {a[i].se, i};
    if (i + 1 < n && sa[i + 1] > sa[i]) {
      sa[i] = sa[i + 1];
    }
  }

  for (int i = m - 1; i >= 0; i--) {
    sb[i] = {b[i].se, i};
    if (i + 1 < m && sb[i + 1] > sb[i]) {
      sb[i] = sb[i + 1];
    }
  }

  // debug(a, b);
  // debug(sa, sb);

  vc<vi> g(n + m);
  vi d(n + m);
  vi ans(n + m, -1);

  rep(i, n) {
    int j = lower_bound(all(b), pii(a[i].se + 1, 0)) - begin(b);
    if (j == m) {
      continue;
    } else {
      int x = n + sb[j].se;
      int y = i;
      g[x].pb(y);
      d[y] += 1;
    }
  }

  rep(i, m) {
    int j = lower_bound(all(a), pii(b[i].se + 1, 0)) - begin(a);
    if (j == n) {
      continue;
    } else {
      int x = sa[j].se;
      int y = n + i;
      g[x].pb(y);
      d[y] += 1;
    }
  }

  queue<int> q;
  rep(i, n + m) {
    if (!d[i]) {
      ans[i] = i < n;
      q.emplace(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      ans[v] = ans[u];
      if (--d[v] == 0) {
        q.emplace(v);
      }
    }
  }

  ans.resize(n);
  cout << count(all(ans), 1) << " " << count(all(ans), -1) << " "
       << count(all(ans), 0) << "\n";
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