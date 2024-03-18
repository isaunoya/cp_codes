#include <bits/stdc++.h>
using namespace std;
const int N = 4e6 + 7;
bool debug = 0;
int n, k, xa, xb, A, B, C, poss, sum, f[N], g[N], ans[N], f1[N], f2[N], f3[N],
    pos[N];
void build(int l, int r, int t) {
  if (l == r) {
    pos[l] = t;
    return;
  }
  int d = (l + r) / 2;
  build(l, d, t << 1);
  build(d + 1, r, t << 1 | 1);
}
void upd(int t) {
  int x = pos[t];
  f1[x] = g[t];
  f2[x] = g[t];
  f3[x] = ans[t - 1];
  while (x > 0) {
    x = x / 2;
    f1[x] = min(f1[x << 1], f1[x << 1 | 1]);
    f2[x] = max(f2[x << 1], f2[x << 1 | 1]);
    f3[x] = min(f3[x << 1], f3[x << 1 | 1]);
  }
}
void dfs1(int l, int r, int t, int ql, int qr) {
  if (l == ql && r == qr) {
    A = min(A, f1[t]);
    B = max(B, f2[t]);
    return;
  }
  int d = (l + r) / 2;
  if (ql <= d)
    dfs1(l, d, t << 1, ql, min(d, qr));
  if (d + 1 <= qr)
    dfs1(d + 1, r, t << 1 | 1, max(d + 1, ql), qr);
}
void dfs2(int l, int r, int t, int ql, int qr) {
  // if(debug){
  //     cout<<l<<","<<r<<","<<A<<","<<B<<","<<C<<","<<f3[t]<<","<<t<<endl;
  //   }
  // if(debug){
  //     cout<<ql<<","<<qr<<","<<A<<","<<B<<","<<C<<endl;
  //   }
  if (poss)
    return;
  if (l == ql && r == qr) {
    // if(debug) cout<<l<<","<<r<<","<<A<<","<<B<<","<<C<<","<<f3[t]<<endl;
    if (min(C, f3[t]) >= max(B, f2[t]) - min(A, f1[t])) {
      A = min(A, f1[t]);
      B = max(B, f2[t]);
      C = min(C, f3[t]);
      return;
    }

    if (l == r) {
      poss = l;
      return;
    }
    int d = (l + r) / 2;

    if (min(C, f3[t << 1 | 1]) >=
        max(B, f2[t << 1 | 1]) - min(A, f1[t << 1 | 1])) {
      A = min(A, f1[t << 1 | 1]);
      B = max(B, f2[t << 1 | 1]);
      C = min(C, f3[t << 1 | 1]);
      dfs2(l, d, t << 1, l, d);
      return;
    } else {
      dfs2(d + 1, r, t << 1 | 1, d + 1, r);
      return;
    }
    return;
  }
  int d = (l + r) / 2;
  if (d + 1 <= qr)
    dfs2(d + 1, r, t << 1 | 1, max(d + 1, ql), qr);
  if (ql <= d)
    dfs2(l, d, t << 1, ql, min(d, qr));
}
void dfs3(int l, int r, int t, int ql, int qr) {
  if (l == ql && r == qr) {
    A = min(A, f1[t]);
    B = max(B, f2[t]);
    C = min(C, f3[t]);
    return;
  }
  int d = (l + r) / 2;
  if (ql <= d)
    dfs3(l, d, t << 1, ql, min(d, qr));
  if (d + 1 <= qr)
    dfs3(d + 1, r, t << 1 | 1, max(d + 1, ql), qr);
}
void upd2(int a, int b) {
  A = xa;
  B = xb;
  C = 2e9;
  dfs3(1, n, 1, a, b - k + 1);
  sum = min(sum, max(C, B - A));
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> k;
  if (k == 1) {
    for (int i = 1; i <= n; i++)
      cout << 0 << "\n";
    return 0;
  }
  for (int i = 1; i <= n; i++)
    cin >> f[i];
  for (int i = 1; i < k; i++)
    ans[i] = 2e9;
  build(1, n, 1);
  for (int i = 1; i < k; i++)
    upd(i);
  for (int i = 1; i <= n; i++) {
    if (i <= k) {
      g[i] = f[i];
    } else
      g[i] = f[i] ^ ans[i - 1];
    if (i < k) {
      upd(i);
      cout << 0 << "\n";
      continue;
    }
    A = g[i], B = g[i], C = 2e9;
    if (i - k + 2 <= i - 1)
      dfs1(1, n, 1, i - k + 2, i - 1);
    xa = A, xb = B;
    poss = 0;
    dfs2(1, n, 1, 1, i - k + 1);
    sum = 2e9;
    if (poss > 0 && poss <= i - k + 1)
      upd2(poss, i);
    if (poss + 1 <= i - k + 1)
      upd2(poss + 1, i);
    ans[i] = sum;
    upd(i);

    debug = 0;

    cout << sum << "\n";
  }
}
