// by Isaunoya
#include <bits/stdc++.h>
using namespace std;

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
// #define int long long

const int _ = 1 << 21;
struct I {
  char fin[_], *p1 = fin, *p2 = fin;
  inline char gc() {
    return (p1 == p2) && (p2 = (p1 = fin) + fread(fin, 1, _, stdin), p1 == p2)
               ? EOF
               : *p1++;
  }
  inline I &operator>>(int &x) {
    bool sign = 1;
    char c = 0;
    while (c < 48)
      ((c = gc()) == 45) && (sign = 0);
    x = (c & 15);
    while ((c = gc()) > 47)
      x = (x << 1) + (x << 3) + (c & 15);
    x = sign ? x : -x;
    return *this;
  }
  inline I &operator>>(double &x) {
    bool sign = 1;
    char c = 0;
    while (c < 48)
      ((c = gc()) == 45) && (sign = 0);
    x = (c - 48);
    while ((c = gc()) > 47)
      x = x * 10 + (c - 48);
    if (c == '.') {
      double d = 1.0;
      while ((c = gc()) > 47)
        d = d * 0.1, x = x + (d * (c - 48));
    }
    x = sign ? x : -x;
    return *this;
  }
  inline I &operator>>(char &x) {
    do
      x = gc();
    while (isspace(x));
    return *this;
  }
  inline I &operator>>(string &s) {
    s = "";
    char c = gc();
    while (isspace(c))
      c = gc();
    while (!isspace(c) && c != EOF)
      s += c, c = gc();
    return *this;
  }
} in;
struct O {
  char st[100], fout[_];
  signed stk = 0, top = 0;
  inline void flush() { fwrite(fout, 1, top, stdout), fflush(stdout), top = 0; }
  inline O &operator<<(int x) {
    if (top > (1 << 20))
      flush();
    if (x < 0)
      fout[top++] = 45, x = -x;
    do
      st[++stk] = x % 10 ^ 48, x /= 10;
    while (x);
    while (stk)
      fout[top++] = st[stk--];
    return *this;
  }
  inline O &operator<<(char x) {
    fout[top++] = x;
    return *this;
  }
  inline O &operator<<(string s) {
    if (top > (1 << 20))
      flush();
    for (char x : s)
      fout[top++] = x;
    return *this;
  }
} out;
#define pb emplace_back
#define fir first
#define sec second

template <class T> inline void cmax(T &x, const T &y) { (x < y) && (x = y); }
template <class T> inline void cmin(T &x, const T &y) { (x > y) && (x = y); }

int n;
const int N = 1e5 + 10;
struct sgt {
#define ls(x) x << 1
#define rs(x) x << 1 | 1
  int tot = 0;
  int tag[N << 2];
  struct function {
    double k, b;
  } func[N];
  double val(int x, int id) { return func[id].k * (x - 1) + func[id].b; }
  void change(int q, int l, int r, int id) {
    if (l == r) {
      if (val(l, id) > val(l, tag[q]))
        tag[q] = id;
      return;
    }
    int mid = l + r >> 1;
    if (func[id].k > func[tag[q]].k) {
      if (val(mid, id) > val(mid, tag[q]))
        change(ls(q), l, mid, tag[q]), tag[q] = id;
      else
        change(rs(q), mid + 1, r, id);
    } else {
      if (val(mid, id) > val(mid, tag[q]))
        change(rs(q), mid + 1, r, tag[q]), tag[q] = id;
      else
        change(ls(q), l, mid, id);
    }
  }
  double query(int q, int l, int r, int x) {
    if (l == r)
      return val(l, tag[q]);
    int mid = l + r >> 1;
    double ans = val(x, tag[q]);
    if (x <= mid)
      ans = max(ans, query(ls(q), l, mid, x));
    else
      ans = max(ans, query(rs(q), mid + 1, r, x));
    return ans;
  }
  void ins(double k, double b) {
    func[++tot] = {k, b};
    change(1, 1, N, tot);
  }
} T;
signed main() {
  scanf("%d", &n);
  rep(i, 1, n) {
    char s[10];
    scanf("%s", s + 1);
    if (s[1] == 'Q') {
      int x;
      scanf("%d", &x);
      double ans = T.query(1, 1, N, x);
      printf("%lf\n", ans);
      printf("%d\n", (int)ans / 100);
    } else {
      double k, b;
      scanf("%lf %lf", &b, &k);
      T.ins(k, b);
    }
  }
  return out.flush(), 0;
}