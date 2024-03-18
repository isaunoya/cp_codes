#include <bits/stdc++.h>
using namespace std;
int n, a[300005], b[300005];

struct nd {
  int l, r, v;
} t[300005];
int m;

struct w {
  char c;
  int l, r;
} r[300005];
int cnt;
int p[300005];
int ban[300005];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);
  for (int i = 0; i < n; i++)
    scanf("%d", b + i);
  int l = 0;
  int pt = 0;
  while (l < n) {
    int r = l;
    while (r + 1 < n && b[r + 1] == b[l]) {
      r += 1;
    }
    t[m] = {l, r, b[l]};
    while (pt < n && a[pt] != b[l]) {
      pt += 1;
    }
    p[m] = pt;
    l = r + 1;
    m++;
  }
  if (pt == n)
    return !printf("NO\n");
  for (int i = m - 1; i >= 0; i--) {
    if (t[i].r <= p[i])
      continue;
    r[cnt++] = {'R', p[i], t[i].r};
    if (t[i].l < p[i] && p[i] < t[i].r) {
      continue;
    } else {
      ban[i] = 1;
    }
  }
  for (int i = 0; i < m; i++) {
    if (ban[i]) {
      continue;
    } else {
      if (t[i].l == p[i]) {
        continue;
      }
      r[cnt++] = {'L', t[i].l, p[i]};
    }
  }
  printf("YES\n");
  printf("%d\n", cnt);
  for (int i = 0; i < cnt; i++) {
    printf("%c %d %d\n", r[i].c, r[i].l, r[i].r);
  }
}
