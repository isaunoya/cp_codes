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

unordered_map<string, int> mp;
unordered_map<int, string> str;

void solve() {
  int n;
  cin >> n;
  vector<vector<string>> tmp;

  int cnt = 0;
  rep(i, n) {
    string s;
    cin >> s;
    vc<string> t;
    t.pb();
    int w = 0;
    rep(j, s.size()) {
      if (s[j] == '.') {
        w += 1;
        t.pb();
        continue;
      }
      t[w] += s[j];
    }
    rep(j, t.size()) {
      if (!mp.count(t[j])) {
        mp[t[j]] = cnt++;
      }
    }
    tmp.pb(t);
  }
  for (auto [x, y] : mp) {
    str[y] = x;
  }
  vc<vi> g(cnt);
  vi deg(cnt);

  rep(i, 1, n) {
    if (tmp[i - 1] == tmp[i])
      continue;
    if (tmp[i - 1].size() == tmp[i].size()) {
      int k = 0;
      while (tmp[i - 1][k] == tmp[i][k]) {
        k += 1;
      }
      auto u = mp[tmp[i - 1][k]];
      auto v = mp[tmp[i][k]];
      g[u].pb(v);
      deg[v] += 1;
    }
  }
  vi d(cnt);
  pqg<pair<string, int>> q;
  rep(i, cnt) if (deg[i] == 0) q.emplace(str[i], i);
  vi id;
  while (!q.empty()) {
    auto [s, u] = q.top();
    id.pb(u);
    q.pop();
    for (auto v : g[u]) {
      if (--deg[v] == 0) {
        q.emplace(str[v], v);
      }
    }
  }

  bool first = true;
  for (auto i : id) {
    if (!first) {
      cout << ".";
    } else {
      first = false;
    }
    cout << str[i];
  }
  cout << "\n";
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