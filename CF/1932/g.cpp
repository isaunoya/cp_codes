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

void exgcd(ll a, ll b, ll &x, ll &y, ll &g) {
  if (!b) {
    x = 1, y = 0, g = a;
    return;
  }
  exgcd(b, a % b, y, x, g), y -= (a / b) * x;
}

// ax + by = gcd

void solve() {
  int n, m, h;
  cin >> n >> m >> h;
  vi l(n), s(n);
  rep(i, n) cin >> l[i];
  rep(i, n) cin >> s[i];
  vc<vi> g(n);

  rep(i, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].pb(y);
    g[y].pb(x);
  }

  pqg<pair<long long, int>> q;
  vc<ll> dis(n, lnf);
  q.emplace(dis[0] = 0, 0);

  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();
    debug(d, u);
    if (d != dis[u]) {
      continue;
    }
    for (auto v : g[u]) {
      // (s[u]-s[v])*t - H*k = l[v]-l[u]
      ll a = s[u] - s[v];
      ll b = h;
      ll g = gcd(a, b);

      ll z = l[v] - l[u];
      if (z % g) {
        continue;
      }

      if (a < 0) {
        a = -a;
        z = -z;
      }
      z = (z % b + b) % b;
      ll x, y;
      exgcd(a, b, x, y, g);
      if (g < 0) {
        g = -g;
        x = -x;
        y = -y;
      }
      // debug(a, b);
      // debug(a * x + b * y, g);
      // a*x+b*y=g
      a /= g;
      b /= g;
      z /= g;
      // ax + by = 1
      // (a, b) = 1
      // debug(a*x+b*y);

      // debug(a,x,b,y,a*x+b*y,g,z);
      // debug(b);
      x = (x % b + b) % b;
      y = (g - a * x) / b;
      debug(a,x,b,y,a*x+b*y,g,z);
      // (x+kb)*z>d
      // (x+kb)>d/z
      ll w = d / z;
      ll k = w / b;
      while ((x + k * b) * z <= d) {
        k++;
      }
      ll dd = (x + k * b) * z;
      // debug(v, d, dd);
      // continue;
      if (dd < dis[v]) {
        q.emplace(dis[v] = dd, v);
      }
    }
  }

  cout << dis.back() << "\n";
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