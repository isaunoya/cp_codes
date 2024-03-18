#include<bits/stdc++.h>
using namespace std;

int n, q;

const int N = 1e5 + 5;
struct seg {
  int f[N * 4], g[N * 4];

  void up(int x) {
    f[x] = max(f[x * 2], f[x * 2 + 1]);
  }

  void build(int l, int r, int p) {
    f[p] = 0;
    g[p] = 0;
    if (l == r) {
      return;
    }
    int m = (l + r) / 2;
    build(l, m, p * 2);
    build(m + 1, r, p * 2 + 1);
    up(p);
  }

  void push(int p, int v) {
    f[p] += v;
    g[p] += v;
  }

  void down(int p) {
    if (g[p] == 0) {
      return;
    }
    push(p * 2, g[p]);
    push(p * 2 + 1, g[p]);
    g[p] = 0;
  }
  void upd(int ql, int qr, int l, int r, int p, int v) {
    if (ql <= l && r <= qr) {
      push(p, v);
      return;
    }
    down(p);
    int m = (l + r) / 2;
    if (ql <= m) {
      upd(ql, qr, l, m, p * 2, v);
    } 
    if (qr > m) {
      upd(ql, qr, m + 1, r, p * 2 + 1, v);
    }

    up(p);
  }
  int query(int ql, int qr, int l, int r, int p) {
    if (ql <= l && r <= qr) {
      return f[p];
    }
    down(p);
    int res = 0;
    int m = (l + r) / 2;
    if (ql <= m) {
      res = max(res, query(ql, qr, l, m, p * 2));
    }
    if (qr > m) {
      res = max(res, query(ql, qr, m + 1, r, p * 2 + 1));
    }
    return res;
  }
} t[11];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> q;
  for (int i = 2; i <= 10; i++) {
    t[i].build(1, n, 1);
  }
  while (q--) {
    string s;
    cin >> s;
    if (s == "MULTIPLY") {
      int l, r, x;
      cin >> l >> r >> x;
      for (int i = 2; i <= 10; i++) {
        int c = 0;
        while (x % i == 0) {
          x /= i;
          c += 1;
        }
        if (c > 0) {
          t[i].upd(l, r, 1, n, 1, c);
        }
      }
    } else {
      int l, r;
      cin >> l >> r;
      int res = 0;
      for (int i = 2; i <= 10; i++) {
        res = max(res, t[i].query(l, r, 1, n, 1));
      }
      cout << "ANSWER " << res << "\n";
    }
  }
  
}