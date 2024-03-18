#include <bits/stdc++.h>
using namespace std;
const int N = 2e2 + 7, M = 4e4 + 7, p = 1e9 + 7;
int n, k, dp[N][M], c[N][N];
int binom(int a, int b) { return c[a][b]; }
int main() {
  for (int i = 0; i <= 200; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++)
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
  }
  cin >> n >> k;
  int ans = 0;
  dp[1][1] = 1, dp[0][0] = 1;
  for (int x = 2; x <= n; x++)
    for (int i = 0; i < x; i++) {
      int j = x - 1 - i;
      for (int a = 0; a <= i * i; a++)
        for (int b = 0; b <= j * j; b++)
          dp[i + j + 1][a + b + x] =
              (dp[i + j + 1][a + b + x] +
               1ll * dp[i][a] * dp[j][b] % p * binom(i + j, i)) %
              p;
    }
  for (int i = 0; i <= n * n; i++) {
    cout << dp[n][i] << " \n"[i == n * n];
  }
  return 0;
}
