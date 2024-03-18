#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x), _##i = ((y) + 1); i < _##i; i++)
#define Rep(i, x, y) for (register int i = (x), _##i = ((y)-1); i > _##i; i--)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const static int _ = 1 << 20;
char fin[_], *p1 = fin, *p2 = fin;
inline char gc() {
  return (p1 == p2) && (p2 = (p1 = fin) + fread(fin, 1, _, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read() {
  bool sign = 1;
  char c = 0;
  while (c < 48)
    ((c = gc()) == 45) && (sign = 0);
  int x = (c & 15);
  while ((c = gc()) > 47)
    x = (x << 1) + (x << 3) + (c & 15);
  return sign ? x : -x;
}
template <class T> inline void print(T x, char c = '\n') {
  (x == 0) && (putchar(48)), (x < 0) && (putchar(45), x = -x);
  static char _st[100];
  int _stp = 0;
  while (x)
    _st[++_stp] = x % 10 ^ 48, x /= 10;
  while (_stp)
    putchar(_st[_stp--]);
  putchar(c);
}
template <class T> inline void cmin(T &x, T y) { (x > y) && (x = y); }
constexpr static int N = 2e5 + 10;
int n, m, a[N], mn[N << 2];
typedef pair<int, int> pii;
vector<pii> vr[N];
void update(const int &x, int l, int r, int rt, const int &val) {
  if (l == r) {
    mn[rt] = val;
    return;
  }
  int mid = l + r >> 1;
  (x <= mid) ? update(x, l, mid, rt << 1, val)
             : update(x, mid + 1, r, rt << 1 | 1, val);
  mn[rt] = mn[rt << 1];
  cmin(mn[rt], mn[rt << 1 | 1]);
}
int query(const int &a, const int &b, int l, int r, int rt) {
  if (a <= l && r <= b) {
    return mn[rt];
  }
  int mid = l + r >> 1, ans = 1e9;
  if (a <= mid)
    cmin(ans, query(a, b, l, mid, rt << 1));
  if (b > mid)
    cmin(ans, query(a, b, mid + 1, r, rt << 1 | 1));
  return ans;
}
struct pri_que {
  priority_queue<int, vector<int>, greater<int>> a, b;
  inline void push(const int &x) { a.push(x); }
  inline void pop(const int &x) { b.push(x); }
  inline int top() {
    while (a.top() == b.top()) {
      a.pop();
      b.pop();
    }
    return a.top();
  }
} q;
int las[N], ans[N], vis[N];
signed main() {
#ifdef _WIN64
  freopen("testdata.in", "r", stdin);
#endif
  n = read();
  m = read();
  rep(i, 1, n) a[i] = read();
  rep(i, 1, m) {
    int l = read(), r = read();
    vr[r].emplace_back(pii(l, i));
  }
  rep(i, 0, 2e5) q.push(i);
  rep(i, 1, n) {
    if (!vis[a[i]])
      vis[a[i]] = 1, q.pop(a[i]);
    if (las[a[i]])
      update(las[a[i]], 1, n, 1, 1e9);
    las[a[i]] = i;
    update(i, 1, n, 1, a[i]);
    for (pii x : vr[i]) {
      ans[x.second] = q.top();
      if (x.first > 1)
        cmin(ans[x.second], query(1, x.first - 1, 1, n, 1));
    }
  }
  rep(i, 1, m) print(ans[i]);
  return 0;
}