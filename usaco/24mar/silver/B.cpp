#include <bits/stdc++.h>
using namespace std;
int n, p;
const int N = 2e5 + 5;
const long long LNF = 1e18;
pair<int, int> pt[N], pp[N];
long long dist(pair<int, int> x, pair<int, int> y) {
  return abs(x.first - y.first) + abs(x.second - y.second);
}
using ar = array<int, 3>;
ar w[2][N];
vector<int> g[2][N];
int rr[N], cnt, vis[N];
long long S[N];
void dfs(int u, int ww) {
  rr[cnt] = u;
  pp[cnt] = pt[u];
  vis[u] = 1;
  cnt++;
  for (auto v : g[ww][u]) {
    if (vis[v]) {
      continue;
    }
    if (!vis[v]) {
      dfs(v, !ww);
      break;
    }
  }
}
map<pair<int, int>, int> which;
vector<int> getE(pair<int, int> t) {
  if (which.count(t)) {
    return {which[t]};
  }
  auto [x, y] = t;
  for (int t = 0; t < 2; t++) {
    int ww = lower_bound(w[t], w[t] + p, array<int, 3>{x, y, 0}) - w[t];
    if (w[t][ww][0] == x && min(w[t][ww][1], w[t][ww ^ 1][1]) <= y &&
        y <= max(w[t][ww][1], w[t][ww ^ 1][1])) {
      return {w[t][ww][2], w[t][ww ^ 1][2]};
    }
    swap(x, y);
  }
  assert(0);
}
long long get(int i, int j) {
  long long w = abs(S[j] - S[i]);
  return min(w, S[p] - w);
}
int c[N], ans[N];
pair<int, int> solve(pair<int, int> a, pair<int, int> b, vector<int> A,
                     vector<int> B) {
  long long mn = LNF, u = -1, v = -1;
  for (auto x : A) {
    for (auto y : B) {
      long long dis = dist(a, pp[x]) + dist(b, pp[y]) + get(x, y);
      if (dis < mn) {
        u = x, v = y, mn = dis;
      }
    }
  }
  if (u > v) {
    swap(u, v);
  }
  return make_pair(u, v);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> p;
  for (int i = 0; i < p; i++) {
    cin >> pt[i].first >> pt[i].second;
    auto [x, y] = pt[i];
    w[0][i] = ar{x, y, i};
    w[1][i] = ar{y, x, i};
  }
  sort(w[0], w[0] + p), sort(w[1], w[1] + p);
  for (int t = 0; t < 2; t++) {
    for (int i = 0, j = 0; i < p; i = j) {
      while (j < p && w[t][i][0] == w[t][j][0]) {
        j++;
      }
      for (int k = i; k < j; k += 2) {
        int x = w[t][k][2];
        int y = w[t][k ^ 1][2];
        g[t][x].push_back(y);
        g[t][y].push_back(x);
      }
    }
  }
  dfs(0, 0);
  S[0] = 0;
  for (int i = 0; i < p; i++) {
    S[i + 1] = S[i] + dist(pp[i], pp[(i + 1) % p]);
    auto [x, y] = pp[i];
    w[0][i] = ar{x, y, i};
    w[1][i] = ar{y, x, i};
    which[pp[i]] = i;
  }
  sort(w[0], w[0] + p), sort(w[1], w[1] + p);
  for (int i = 0; i < n; i++) {
    pair<int, int> a, b;
    cin >> a.first >> a.second >> b.first >> b.second;
    auto A = getE(a), B = getE(b);
    sort(A.begin(), A.end()), sort(B.begin(), B.end());
    if (A != B) {
      auto [u, v] = solve(a, b, A, B);
      if (S[v] - S[u] == get(u, v)) {
        c[u]++;
        c[v + 1]--;
      } else {
        c[0]++;
        c[u + 1]--;
        c[v]++;
      }
    }
  }
  for (int i = 0; i < p; i++) {
    c[i + 1] += c[i], ans[rr[i]] = c[i];
  }
  for (int i = 0; i < p; i++) {
    cout << ans[i] << "\n";
  }
  return 0;
}