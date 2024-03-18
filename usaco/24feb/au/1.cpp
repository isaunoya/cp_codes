#include <bits/stdc++.h>
#define rep1(a) for (auto i = 0; i < a; i++)
#define rep2(i, a) for (auto i = 0; i < a; i++)
#define rep3(i, a, b) for (auto i = a; i < b; i++)
#define rep4(i, a, b, c) for (auto i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define all(v) (v).begin(), (v).end()
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
const int lnf = 2e9;
const int N = 5e4 + 5;
unordered_map<int, ll> ok[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, c, r, k;
  cin >> n >> m >> c >> r >> k;

  vc<vc<pii>> g(n);
  rep(i, m) {
    int x, y, z;
    cin >> x >> y >> z;
    --x;
    --y;
    g[x].pb(y, z);
    g[y].pb(x, z);
  }

  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>>
      q;
  rep(i, c) { q.emplace(ok[i][i] = 0, i, i); }

  auto get = [&](int u) {
    vc<int> list;
    for (auto [x, y] : ok[u]) {
      list.pb(y);
    }
    if ((int)list.size() < k) {
      return lnf;
    } else {
      sort(all(list));
      return list[k - 1];
    }
  };
  while (!q.empty()) {
    auto [d, u, from] = q.top();
    q.pop();
    if (d > r) {
      break;
    }
    if (d > ok[u][from]) {
      continue;
    }
    for (auto [v, w] : g[u]) {
      int cur = get(v);
      if (cur <= d + w) {
        continue;
      }
      if (!ok[v].count(from) || ok[v][from] > d + w) {
        q.emplace(ok[v][from] = d + w, v, from);
      }
    }
  }

  vi res;
  rep(i, c, n) {
    if (get(i) <= r) {
      res.pb(i);
    }
  }

  cout << res.size() << "\n";

  for (int i : res) {
    cout << i + 1 << "\n";
  }
  return 0;
}