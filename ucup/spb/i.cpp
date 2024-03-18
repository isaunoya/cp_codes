#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1000005;
int n;
int main() {
  scanf("%d", &n);
  int mn, mx = n;
  if (n & 1) {
    int mid = n / 2 + 1;
    mn = 1;
    for (int i = mid - 3; i >= 1; i -= 3)
      mn++;
    for (int i = mid + 3; i <= n; i += 3)
      mn++;
  } else {
    int mid1 = n / 2, mid2 = n / 2 + 1;
    mn = 2;
    for (int i = mid1 - 3; i >= 1; i -= 3)
      mn++;
    for (int i = mid2 + 3; i <= n; i += 3)
      mn++;
  }
  printf("%d %d", mn, mx);
  return 0;
}
