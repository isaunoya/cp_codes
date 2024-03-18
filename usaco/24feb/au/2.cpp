#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

#define eb emplace_back

using namespace std;

typedef long long LL;
constexpr int N = 1000005;

int n, a[N];
int r[N], stk[N], tt;
LL res[N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  memcpy(a + n, a, n << 2);
  stk[0] = 2 * n;
  for (int i = 2 * n - 1; i >= n; --i) {
    while (a[i] < a[stk[tt]]) {
      --tt;
    }
    stk[++tt] = i;
  }
  for (int i = tt; i; --i) {
    res[stk[i] - (n - 1)] += a[stk[i]];
    res[stk[i - 1] - (n - 1)] -= a[stk[i]];
  }
  for (int i = n - 1; ~i; --i) {
    while (a[i] < a[stk[tt]]) {
      res[stk[tt] - i] -= a[stk[tt]];
      res[stk[tt - 1] - i] += a[stk[tt]];
      --tt;
    }
    res[0] += a[i];
    res[stk[tt] - i] -= a[i];
    stk[++tt] = i;
  }
  while (tt) {
    res[stk[tt] + 1] -= a[stk[tt]];
    res[stk[tt - 1] + 1] += a[stk[tt]];
    --tt;
  }
  for (int i = 1; i <= n; ++i) {
    res[i] += res[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    res[i] += res[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    printf("%lld\n", res[i]);
  }
  return 0;
}