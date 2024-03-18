#include <bits/stdc++.h>
#include <iterator>
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

using namespace std;
int n;
string A[10], B[10];
char op[10];
int equal_len[10];

int f[36];
int find(int x) {
  if (f[x] == x)
    return x;
  return f[x] = find(f[x]);
}

int get(char c) {
  if (isdigit(c))
    return c - 48 + 26;
  else {
    return c - 'A';
  }
}
vector<int> e[36], g[36];
int id[36], c = 0, vis[36];
vector<int> w;
void dfse(int x) {
  if (vis[x])
    return;
  id[x] = c++;
  vis[x] = 1;
  w.push_back(x);
  for (auto y : e[x])
    dfse(y);
}
const int P = 998244353;
using ll = long long;
ll ans = 0;
ll ned[36], ff[1 << 20], dp[15][1 << 15], ww[15];
void solve_it() {
  for (int i = 0; i < c; i++) {
    ned[i] = 0;
    int x = w[i];
    for (auto j : g[x])
      ned[i] |= 1 << id[j];
  }
  ff[0] = 0;
  for (int i = 1; i < (1 << c); i++) {
    int t = i & -i;
    ff[i] = ff[i ^ t] | ned[__lg(t)];
  }
  for (int i = 0; i <= 10; i++)
    for (int j = 0; j < (1 << c); j++)
      dp[i][j] = 0;
  dp[0][0] = 1;
  for (int i = 0; i < 10; i++)
    ww[i] = 0;
  for (int i : w) {
    int x = find(i);
    if (x >= 26) {
      x -= 26;
      ww[x] |= 1 << id[i];
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < (1 << c); j++) {
      for (int t = j;; t = (t - 1) & j) {
        int prev_j = j ^ t;
        if (((t & ww[i]) == ww[i]) && ((prev_j & ff[t]) == ff[t])) {
          dp[i + 1][j] += dp[i][prev_j];
          if (dp[i + 1][j] >= P) {
            dp[i + 1][j] -= P;
          }
        }
        if (t == 0)
          break;
      }
    }
  }
}

void solve() {
  for (int i = 0; i < 36; i++)
    f[i] = i, g[i].clear(), e[i].clear(), vis[i] = 0, id[i] = -1;
  bool ok = true;
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < equal_len[i]; k++) {
      int u = get(A[i][k]), v = get(B[i][k]);
      int fu = find(u), fv = find(v);
      if (fu > fv)
        swap(fu, fv); // fu<fv
      f[fu] = fv;
    }
  }
  rep(i, n) {
    if (op[i] == '=')
      continue;
    int l = equal_len[i], u = get(A[i][l]), v = get(B[i][l]);
    u = find(u), v = find(v);
    // debug(u, v);
    if (u == v) {
      ok = false;
      break;
    }
    if (op[i] == '<') { // v>u
      g[v].push_back(u);
      e[u].push_back(v);
      e[v].push_back(u);
    } else { // u>v
      g[u].push_back(v);
      e[u].push_back(v);
      e[v].push_back(u);
    }
  }
  if (!ok)
    return;
  vector<int> deg(36);
  rep(i, 36) for (auto j : g[i]) deg[j]++;
  queue<int> q;
  rep(i, 36) if (deg[i] == 0) q.emplace(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (--deg[v] == 0)
        q.emplace(v);
    }
  }
  rep(i, 36) ok &= (deg[i] == 0);
  // debug(ok);
  if (!ok)
    return;
  for (int i = 26; i < 36; i++)
    if (find(i) != i)
      return;
  ll res = 1;
  for (int i = 0; i < 36; i++) {
    int foo = find(i);
    if (vis[foo])
      continue;
    dfse(foo);
    solve_it();
    res = res * dp[10][(1 << c) - 1] % P;
    for (int bar : w)
      id[bar] = -1;
    w.clear();
    c = 0;
  }
  debug(res);
  ans += res;
  if (ans >= P) {
    ans -= P;
  }
}
void dfs(int u) {
  if (u == n) {
    solve();
    return;
  }
  if (op[u] == '=') {
    equal_len[u] = A[u].size();
    dfs(u + 1);
  } else {
    for (int j = 0; j < (int)A[u].size(); j++)
      if (A[u][j] != B[u][j]) {
        equal_len[u] = j;
        dfs(u + 1);
      }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int p = -1, l = s.size();
    for (int j = 0; j < l; j++) {
      if (s[j] == '=' || s[j] == '<' || s[j] == '>') {
        p = j;
        break;
      }
    }
    op[i] = s[p];
    A[i] = string(s.begin(), s.begin() + p);
    B[i] = string(s.begin() + p + 1, s.end());
    while (A[i].size() < B[i].size())
      A[i] = "0" + A[i];
    while (B[i].size() < A[i].size())
      B[i] = "0" + B[i];
  }
  dfs(0);
  cout << ans << "\n";
}
