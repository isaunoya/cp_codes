#include <bits/stdc++.h>
using namespace std;

const int maxn = 500010;
int n, m, a[maxn], b[maxn], c[maxn], f[maxn], val[maxn * 2];

void add(int p, int v) {
  for (p += maxn; p < maxn * 2; p += p & -p)
    val[p] = min(val[p], v);
}

void reset(int p) {
  for (p += maxn; p < maxn * 2; p += p & -p)
    val[p] = 1e9;
}

int query(int p) {
  int s = 1e9;
  for (p += maxn; p; p -= p & -p)
    s = min(s, val[p]);
  return s;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  a[++n] = INT_MAX;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &b[i]);
  }
  sort(b + 1, b + m + 1);
  for (int i = 0; i <= n; i++) {
    c[i] = lower_bound(b + 1, b + m + 1, a[i]) - b - i;
  }
  memset(f, 0x3f, sizeof(f)), f[0] = 0;
  memset(val, 0x3f, sizeof(f));
  function<void(int, int)> solve = [&](int l, int r) {
    if (l == r)
      return;
    int mid = (l + r) / 2;
    solve(l, mid);
    vector<array<int, 2>> L, R;
    for (int i = l; i <= r; i++) {
      (i <= mid ? L : R).push_back({a[i], i});
    }
    sort(L.begin(), L.end()), sort(R.begin(), R.end());
    for (int i = 0, j = 0; i < R.size(); i++) {
      for (; j < L.size() && L[j][0] < R[i][0]; j++) {
        int k = L[j][1];
        add(c[k] - 1, f[k] - k - 1);
      }
      int k = R[i][1];
      f[k] = min(f[k], query(c[k]) + k);
    }
    for (auto &p : L)
      reset(c[p[1]] - 1);
    solve(mid + 1, r);
  };
  solve(0, n);
  printf("%d\n", f[n] > 1e9 ? -1 : f[n]);
  return 0;
}