#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7, p = 998244353;
unsigned long long E[N], op[N];
int n, f[N], g[N], f1[N], f2[N], F[N];
int h(int u) {
  if (F[u] == u)
    return u;
  return F[u] = h(F[u]);
}
int main() {
  cin >> n;
  int ans = (p + 1) / 2, res = (p + 1) / 2;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &f[i]), g[f[i]]++;
    if (g[f[i]] == 1)
      ans = ans * 2 % p;
    if (g[f[i]] % 2 == 0)
      f1[++f1[0]] = f[i];
    else
      f2[++f2[0]] = f[i];
  }
  if (f1[0] != f2[0])
    res = 0;
  for (int i = 1; i <= f1[0]; i++)
    if (f1[i] != f2[i])
      res = 0;
  for (int i = 1; i <= 200000; i++)
    F[i] = i,
    E[i] = 1ull * rand() * rand() * rand() * rand() * rand() * rand() * rand();
  for (int i = n; i >= 1; i--)
    op[i] ^= E[f[i]];
  for (int i = 1; i <= n; i++)
    op[i] ^= op[i - 1];
  int pos = 0;
  memset(g, 0, sizeof(g));
  for (int i = 1; i <= n; i++) {
    if (op[i] == 0) {
      int C = 0;
      for (int j = pos + 1; j <= i; j++) {
        g[f[j]]++;
        if (g[f[j]] == 1) {
          if (C > 0)
            F[h(C)] = h(f[j]);
          C = f[j];
        }
      }
      for (int j = pos + 1; j <= i; j++) {
        g[f[j]]--;
      }
      pos = i;
    }
  }
  for (int i = 1; i <= n; i++)
    g[f[i]]++;
  for (int i = 1; i <= 200000; i++)
    if (g[i] && h(i) == i)
      res = res * 2 % p;
  cout << (ans - res + p) % p << endl;
  return 0;
}
// 1 1 2 2 1 2 1 2
