#include <bits/stdc++.h>
using namespace std;
const int N = 1007;
int n, a[N][N];
long long F[N];
int main() {
  cin >> n;
  int g = 4000000;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &a[i][j]);
      if (a[i][j] == -1)
        a[i][j] = 0;
      F[(j - i + n) % n] += a[i][j];
    }
  }
  sort(F, F + n);
  cout << F[n - 1] - F[0] << endl;
}
