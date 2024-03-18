#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int M = 998244353;
const int B = 26;
int n, ans;
struct node {
  int op, x, y;
  // op=-1: mk[x] &= y
  // op=0:  val[x] = val[y]
  // op=1:  val[x] < val[y]
};
vector<node> limits;
string s[10], l[10], r[10];
int op[B];
void add(int &x, int y) {
  x += y;
  if (x >= M)
    x -= M;
}
int find_operator(string &S) {
  for (int i = 0; i < S.size(); i++)
    if (S[i] == '<' || S[i] == '>' || S[i] == '=')
      return i;
  assert(0);
}
bool is_digit(char x) { return x >= '0' && x <= '9'; }
vector<int> G[B], invG[B];
int ban[B], id[B], mk[B], deg[B], pre[B], ccnt;
int ffind(int x) {
  if (pre[x] == x)
    return x;
  return pre[x] = ffind(pre[x]);
}
struct edge {
  int x, y;
};
bool vis[B];
bool toposort() { // 1: no cycle, 0: cycle
  queue<int> Q;
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < B; i++)
    if (!ban[i] && !deg[i])
      Q.push(i);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    vis[u] = 1;
    for (auto v : G[u]) {
      deg[v]--;
      if (!deg[v])
        Q.push(v);
    }
  }
  for (int i = 0; i < B; i++)
    if (!ban[i] && !vis[i])
      return 0;
  return 1;
}
bool layer[1 << 11], valid[1 << 11];
int dp[1 << 11], tmp[1 << 11], Mk[11], mk_v[10];
void Dfs(int u) {
  id[u] = ccnt++;
  for (int i = 0; i < 10; i++)
    if ((mk[u] >> i) & 1)
      mk_v[i] |= 1 << id[u];
  vis[u] = 1;
  for (auto v : G[u]) { // u < v
    if (!vis[v])
      Dfs(v);
    Mk[id[u]] |= 1 << id[v];
  }
  for (auto v : invG[u]) {
    if (!vis[v])
      Dfs(v);
  }
}
int get_dp() {
  int m = ccnt;
  for (int i = 0; i < (1 << m); i++) {
    layer[i] = valid[i] = 1;
    for (int j = 0; j < m; j++)
      if (Mk[j] & i) {
        if ((i >> j) & 1)
          layer[i] = 0;
        else
          valid[i] = 0;
      }
  }
  for (int i = 0; i < (1 << m); i++)
    dp[i] = tmp[i] = 0;
  dp[0] = 1;
  for (int d = 0; d < 10; d++) {
    for (int i = 0; i < (1 << m); i++)
      tmp[i] = 0;
    for (int i = 0; i < (1 << m); i++) {
      int r = mk_v[d] & ((1 << m) - 1 - i);
      for (int j = r;; j = (j - 1) & r) {
        if (layer[j])
          add(tmp[i | j], dp[i]);
        if (!j)
          break;
      }
    }
    for (int i = 0; i < (1 << m); i++)
      dp[i] = (valid[i]) ? tmp[i] : 0;
  }
  return dp[(1 << m) - 1];
}
int work() {
  for (int i = 0; i < B; i++)
    id[i] = -1, invG[i].clear(), G[i].clear(), pre[i] = i,
    mk[i] = (1 << 10) - 1, deg[i] = 0;
  vector<edge> E;
  for (auto e : limits) {
    if (e.op == -1)
      mk[e.x] &= e.y;
    else if (e.op == 0)
      pre[ffind(e.y)] = ffind(e.x);
    else
      E.pb((edge){e.x, e.y});
  }
  for (int i = 0; i < B; i++)
    mk[ffind(i)] &= mk[i], ban[i] = (pre[i] != i);
  for (auto e : E) {
    int x = ffind(e.x), y = ffind(e.y);
    if (x == y)
      return 0;
    G[x].pb(y);
    invG[y].pb(x);
    deg[y]++;
  }
  if (!toposort())
    return 0;
  int ret = 1;
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < B; i++)
    if (!ban[i] && !vis[i]) {
      memset(mk_v, 0, sizeof(mk_v));
      memset(Mk, 0, sizeof(Mk));
      ccnt = 0;
      Dfs(i);
      ret = 1ll * ret * get_dp() % M;
    }
  return ret;
}
int add_limit(char x, char y, int op) {
  //-1 invalid, 0 no limit, 1 one limit
  if (is_digit(x) && is_digit(y)) {
    if (op == 0 && x == y)
      return 0;
    if (op == 1 && x < y)
      return 0;
    return -1;
  }
  if (!is_digit(x) && !is_digit(y)) {
    limits.pb((node){op, x - 'A', y - 'A'});
    return 1;
  }
  if (op == 0) { // x = y
    if (!is_digit(x)) {
      limits.pb((node){-1, x - 'A', 1 << (y - '0')});
    } else {
      limits.pb((node){-1, y - 'A', 1 << (x - '0')});
    }
  } else { // x < y
    if (!is_digit(x)) {
      if (y == '0')
        return -1;
      int res = 0;
      for (int i = 0; i < y - '0'; i++)
        res |= 1 << i;
      limits.pb((node){-1, x - 'A', res});
    } else {
      if (x == '9')
        return -1;
      int res = 0;
      for (int i = 9; i > x - '0'; i--)
        res |= 1 << i;
      limits.pb((node){-1, y - 'A', res});
    }
  }
  return 1;
}
void dfs(int x) {
  if (x == n) {
    add(ans, work());
    return;
  }
  int len = l[x].size();
  int cur_size = limits.size();
  if (op[x] == 0) {
    bool flag = 1;
    for (int i = 0; i < len; i++)
      flag &= add_limit(l[x][i], r[x][i], 0) >= 0;
    if (flag)
      dfs(x + 1);
  } else {
    bool flag = 1;
    for (int i = 0; i < len; i++) {
      int pp = add_limit(l[x][i], r[x][i], 1);
      if (pp >= 0 && flag)
        dfs(x + 1);
      if (pp == 1)
        limits.pop_back();
      flag &= add_limit(l[x][i], r[x][i], 0) >= 0;
    }
  }
  while (limits.size() > cur_size)
    limits.pop_back();
}
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    int len = (int)s[i].size();
    string L = "", R = "";
    int p = find_operator(s[i]);
    for (int j = 0; j < s[i].size(); j++) {
      if (j < p)
        L += s[i][j];
      if (j > p)
        R += s[i][j];
    }
    while (L.size() < R.size())
      L = '0' + L;
    while (R.size() < L.size())
      R = '0' + R;
    if (s[i][p] == '=')
      op[i] = 0;
    else
      op[i] = 1;
    if (s[i][p] == '>')
      swap(L, R);
    l[i] = L;
    r[i] = R;
  }
  dfs(0);
  cout << ans << endl;
  return 0;
}