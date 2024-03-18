#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 300005;
const int INF = 1e9;
int n;
int c[N];
int p[N];
vector<int> G[N];
int mx[N], mn[N];
long long ans;
void dfs(int u) {
  mn[u] = INF;
  if (G[u].empty())
    mx[u] = mn[u] = c[u];
  for (int v : G[u]) {
    dfs(v);
    if (G[v].empty())
      ans += (long long)c[u] * c[v];
    else {
      if (c[u] < c[v]) {
        ans -= (long long)(c[v] - c[u]) * mx[v];
      } else {
        if ((long long)(c[u] - c[v]) * mn[v] < (long long)c[u] * c[v])
          ans += (long long)(c[u] - c[v]) * mn[v];
        else
          ans += (long long)c[u] * c[v];
      }
    }
    mx[u] = max(mx[u], mx[v]);
    mn[u] = min(mn[u], mn[v]);
  }
  //    cerr<<"now"<<u<<" "<<ans<<"\n";
  return;
}
int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++)
    scanf("%d", &p[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]);
  for (int i = 2; i <= n; i++)
    G[p[i]].emplace_back(i);
  dfs(1);
  printf("%lld", ans);
  return 0;
}