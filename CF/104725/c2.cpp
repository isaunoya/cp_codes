#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn = 305, tt = 998244353;
int T, n, k, m, d[maxn][maxn], lnk[maxn][maxn], a[maxn][maxn], b[maxn][maxn],
    c[maxn][maxn], z[maxn][maxn];
LL qsm(LL w, int b) {
  LL num = 1;
  while (b) {
    if (b & 1)
      num = num * w % tt;
    w = w * w % tt;
    b >>= 1;
  }
  return num;
}
LL det(int a[maxn][maxn], int n) {
  LL ans = 1;
  for (int t = 1; t <= n; t++) {
    int h = 0;
    for (int i = t; i <= n; i++)
      if (a[i][t]) {
        h = i;
        break;
      }
    swap(a[t], a[h]);
    if (!h)
      return 0;
    for (int i = t + 1; i <= n; i++) {
      LL num = qsm(a[t][t], tt - 2) * a[i][t] % tt;
      for (int j = t; j <= n; j++)
        a[i][j] = (a[i][j] - num * a[t][j] % tt + tt) % tt;
    }
    ans = ans * a[t][t] % tt;
  }
  return ans;
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    lnk[x][y] = 1;
    d[y][y]++;
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (i == j)
        z[i][j] = ((LL)n * k % tt - d[i][i] + tt - 1) % tt;
      else
        z[i][j] = (lnk[i][j] - 1 + tt) % tt;
  if (k == 1) {
    for (int i = 1; i < n; i++)
      for (int j = 1; j < n; j++)
        a[i][j] = z[i + 1][j + 1];
    printf("%lld\n", det(a, n - 1));
    return 0;
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      if (i == n)
        c[i][j] = 1;
      else
        c[i][j] = z[i][j];
      b[i][j] = (z[i][j] + 1) % tt;
      a[i - 1][j - 1] = (z[i][j] - z[1][j] + tt) % tt;
    }
  for (int i = 1; i <= n; i++) {
  	for (int j = 1; j <= n; j++) {
  		printf("%d ", a[i][j]);
  	}
  	printf("\n");
  }
  for (int i = 1; i <= n; i++) {
  	for (int j = 1; j <= n; j++) {
  		printf("%d ", b[i][j]);
  	}
  	printf("\n");
  }
  for (int i = 1; i <= n; i++) {
  	for (int j = 1; j <= n; j++) {
  		printf("%d ", c[i][j]);
  	}
  	printf("\n");
  }
  printf("%lld\n", det(a, n - 1) * qsm(det(b, n), k - 2) % tt * det(c, n) % tt);
  return 0;
}
