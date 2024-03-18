#include <bits/stdc++.h>
using namespace std;
const int N = 25;
char s[N][N];
int n;
int a[N], ans[N], dp[1 << N];
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%s", s[i]);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      if (s[i][j] == '1')
        a[i] += (1 << j);
  }
  dp[1] = 1;
  for (int i = 1; i < (1 << n); i++)
    if (dp[i]) {
      int x = 0;
      for (int j = 0; j < n; j++)
        if ((dp[i] >> j) & 1)
          x |= a[j];
      x -= (x & i);
      for (int j = 0; j < n; j++)
        if ((x >> j) & 1)
          dp[i | (1 << j)] |= (1 << j);
    }
  for (int i = 1; i < (1 << n); i++)
    if (dp[i]) {
      int x = dp[(1 << n) - i];
      for (int j = 0; j < n; j++)
        if ((dp[i] >> j) & 1)
          ans[j] |= x;
    }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%d", (ans[i] >> j) & 1);
    printf("\n");
  }
}