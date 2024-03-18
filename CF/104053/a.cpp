#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 7;
long long F[2][N][N], G[2][N], E[N], R[N], a[N], b[N];
int t, n, siz[N];
vector<int> v[N];
void dfs(int u, int fa) {
  siz[u] = 1;
  bool flag = 0;
  F[0][u][0] = F[1][u][0] = 0;
  for (int i = 0; i < v[u].size(); i++) {
    int x = v[u][i];
    if (x == fa)
      continue;
    dfs(x, u), flag = 1;
  }
  E[0] = 0;
  for (int i = 0; i < v[u].size(); i++) {
    int x = v[u][i];
    if (x == fa)
      continue;
    for (int t = 0; t <= siz[u] + siz[x]; t++)
      G[0][t] = G[1][t] = 1e18, R[t] = 1e18;
    for (int f1 = 0; f1 <= siz[u]; f1++)
      for (int f2 = 0; f2 <= siz[x]; f2++) {
        G[0][f1 + f2] = min(G[0][f1 + f2], F[0][u][f1] + F[0][x][f2]);
        G[1][f1 + f2] = min(G[1][f1 + f2], F[1][u][f1] + F[0][x][f2]);
        G[1][f1 + f2] = min(G[1][f1 + f2], F[0][u][f1] + F[1][x][f2]);
        R[f1 + f2] = min(R[f1 + f2], E[f1] + min(F[1][x][f2], F[0][x][f2]));
      }
    siz[u] += siz[x];
    for (int t = 0; t <= siz[u]; t++)
      F[0][u][t] = G[0][t], F[1][u][t] = G[1][t], E[t] = R[t];
  }
  if (!flag) {
    F[0][u][0] = a[u];
    F[1][u][0] = 0;
    F[0][u][1] = 0;
  }
  for (int i = 0; i <= siz[u]; i++)
    F[0][u][i] = min(F[0][u][i], E[i] + a[u]);
}
signed main() {
  cin >> t;
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      v[i].resize(0), siz[i] = 0;
    for (int i = 1; i <= n; i++)
      scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++)
      scanf("%lld", &b[i]);
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      v[x].push_back(y);
      v[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
      for (int j = 0; j <= n; j++)
        F[0][i][j] = F[1][i][j] = 1e18;
    dfs(1, 0);
    long long ans = 1e18;
    for (int i = 0; i <= n; i++)
      ans = min(ans, b[i] + min(F[0][1][i], F[1][1][i]));
    cout << ans << endl;
  }
  return 0;
}