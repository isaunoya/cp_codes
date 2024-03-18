#include <bits/stdc++.h>
using namespace std;
const int N = 500;
const int T = 500;
const int P = 998244353;
int pool[N + 1][N + 1][T * 2 + 1];
int *dp[N + 1][N + 1];
void mod(int &x) {
  if (x >= P)
    x -= P;
}
int main() {
  ios::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<int> xl(n), xr(n);
  for (int i = 0; i < n; i++) {
    cin >> xl[i] >> xr[i];
    xr[i]++;
  }
  vector<int> yl(m), yr(m);
  for (int i = 0; i < m; i++) {
    cin >> yl[i] >> yr[i];
    yr[i]++;
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      dp[i][j] = pool[i][j] + T;
    }
  }

  dp[0][0][0] = 1;
  dp[0][0][1] = P - 1;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = -T; k < T; k++) {
        mod(dp[i][j][k + 1] += dp[i][j][k]);
      }
      if (i < n) {
      	for (int k = -T; k < 0; k++) {
      		mod(dp[i + 1][j][k + xl[i]] += dp[i][j][k]);
      		mod(dp[i + 1][j][k + xr[i]] += P - dp[i][j][k]);
      	}
      }
      if (j < m) {
      	for (int k = 0; k <= T; k++) {
      		mod(dp[i][j + 1][k - yr[j] + 1] += dp[i][j][k]);
      		mod(dp[i][j + 1][k - yl[j] + 1] += P - dp[i][j][k]);
      	}
      }
    }
  }
  for (int i = 0; i < n; i++) {
  	for (int j = 0; j < m; j++) {
  		cout << dp[i + 1][j + 1][0] << " \n"[j + 1 == m];
  	}
  }
}