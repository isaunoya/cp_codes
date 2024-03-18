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
  int N;
  cin >> N;
  vi a(N);
  rep(i, N) cin >> a[i];
  vc<vi> e(N);
  rep(i, N - 1) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    e[u].pb(v);
    e[v].pb(u);
  }
  vc<ll> ans(N);
  rep(j, 0, 20) {
    vi b(N);
    rep(i, N) { b[i] = a[i] >> j & 1; }
    vc<vc<array<ll, 2>>> F(2, vc<array<ll, 2>>(N));
    vi s(N, 1);
    auto dfs2 = [&](auto self, int u, int p) ->void{
      if (!u)
        F[0][u][!b[u]] = 1;
      for (auto v : e[u]) {
        if (v != p) {
          F[0][v][b[v]] += F[0][u][b[u]];
          F[0][v][b[v]] -= F[1][v][b[u]];
          F[0][v][b[v]] += (b[u] ^ b[v]) * (N - s[v]);
          F[0][v][b[v]] += F[1][u][b[u]];
          F[0][v][!b[v]] += N - s[v];
          F[0][v][!b[v]] += F[0][v][b[v]];
          self(self, v, u);
        }
      }
    };
    auto dfs = [&](auto self, int u, int p) ->void{
      for (auto v : e[u]) {
        if (v != p) {
          self(self, v, u);
          F[1][u][b[u]] += F[1][v][b[u]];
          s[u] += s[v];
        }
      }
      F[1][u][!b[u]] = F[1][u][b[u]] + s[u];
    };
    dfs(dfs, 0, -1);
    dfs2(dfs2, 0, -1);
    for (int i = 0; i < N; i++) {
      ans[i] += (1LL << j) * (F[1][i][b[i]] + F[0][i][b[i]]);
    }
  }
  for (int i = 0; i < N; i++) {
    cout << ans[i] << " \n"[i + 1 == N];
  }
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