#include <bits/stdc++.h>
using namespace std;
const int P = 998244353;
int n;
vector<int> g[55];
int X[55];
int sz[55];
void dfs(int u, int p) {
  sz[u] = 1;
  X[u] = 0;
  vector<int> son;
  for (auto v : g[u]) {
    if (v == p) {
      continue;
    }
    dfs(v, u);
    son.push_back(v);
    sz[u] += sz[v];
  }
  sort(son.begin(), son.end(), [&](int x, int y) {
    if (X[x] == X[y]) {
      return sz[x] < sz[y];
    }
    return X[x] < X[y];
  });
  long long tmp = 0;
  for (int i = 0; i < son.size(); i++) {
    tmp = (tmp + 1ll * X[son[i]] * (i + 2858) % P) % P;
  }
  X[u] = (tmp * 99ll + 1) % P;
}

vector<int> p;
void dfs2(int u1, int p1, int u2, int p2) {
  swap(p[u1], p[u2]);
  vector<int> son1, son2;
  for (auto v : g[u1])
    if (v != p1)
      son1.push_back(v);
  for (auto v : g[u2])
    if (v != p2)
      son2.push_back(v);
  sort(son1.begin(), son1.end(), [&](int x, int y) {
    if (X[x] == X[y]) {
      return sz[x] < sz[y];
    }
    return X[x] < X[y];
  });
  sort(son2.begin(), son2.end(), [&](int x, int y) {
    if (X[x] == X[y]) {
      return sz[x] < sz[y];
    }
    return X[x] < X[y];
  });
  int sz = son1.size();
  for (int i = 0; i < sz; i++) {
    int v1 = son1[i];
    int v2 = son2[i];
    dfs2(v1, u1, v2, u2);
  }
}

vector<vector<int>> ans;
void solve(vector<int> v, int rt) {
  int m = v.size();
  for (int i = 0, j = 0; i < m; i = j) {
    while (j < m && X[v[i]] == X[v[j]] && sz[v[i]] == sz[v[j]]) {
      j += 1;
    }
    for (int k = i + 1; k < j; k++) {
      iota(p.begin(), p.end(), 0);
      dfs2(v[i], rt, v[k], rt);
      ans.emplace_back(p);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  p.resize(n);
  vector<pair<int, int>> E;
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
    E.emplace_back(x, y);
  }

  for (int i = 0; i < n; i++) {
    dfs(i, -1);
    auto son = g[i];
    sort(son.begin(), son.end(), [&](int x, int y) {
      if (X[x] == X[y]) {
        return sz[x] < sz[y];
      }
      return X[x] < X[y];
    });
    solve(son, i);
  }

  for (auto [x, y] : E) {
    dfs(x, y);
    dfs(y, x);
    if (X[x] == X[y] && sz[x] == sz[y]) {
      iota(p.begin(), p.end(), 0);
      dfs2(x, y, y, x);
      ans.emplace_back(p);
    }
  }
  if (ans.size() == 0) {
    cout << 1 << "\n";
    for (int i = 0; i < n; i++) {
      cout << i + 1 << " \n"[i + 1 == n];
    }
    return 0;
  }
  cout << ans.size() << "\n";
  for (auto v : ans) {
    for (auto vi : v) {
      cout << vi + 1 << " ";
    }
    cout << "\n";
  }
}