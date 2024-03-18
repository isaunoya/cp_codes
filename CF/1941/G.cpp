#if defined(LOCAL)
#include <D:/cp/templates/my_template_compiled.hpp>
#else
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#define debug(...) 42
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
template <typename T> using vc = vector<T>;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second
#endif

vector<pii> eg[400005];
int dis[4000005], vis[4000005];
void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> col;
  for (int i = 1; i <= m; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    col.emplace_back(z);
    eg[x].emplace_back(pii{n + z, 1});
    eg[y].emplace_back(pii{n + z, 1});
    eg[n + z].emplace_back(pii{x, 0});
    eg[n + z].emplace_back(pii{y, 0});
  }
  int st, ed;
  cin >> st >> ed;
  auto spfa = [&]() -> void {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    dis[st] = 0;
    q.push(pii{0, st});
    while (!q.empty()) {
      int now = q.top().second;
      q.pop();
      if (vis[now])
        continue;
      vis[now] = 1;
      for (auto [t, v] : eg[now]) {
        if (dis[t] > dis[now] + v) {
          dis[t] = dis[now] + v;
          q.push(pii{dis[t], t});
        }
      }
    }
  };
  spfa();
  cout << dis[ed] << "\n";
  for (int i = 1; i <= n; ++i)
    dis[i] = INF, vis[i] = 0, eg[i].clear();
  for (int x : col) {
    dis[x + n] = INF;
    vis[x + n] = 0;
    eg[x + n].clear();
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(dis, 0x3f, sizeof dis);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}