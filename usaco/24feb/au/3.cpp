#include <stdio.h>
#include <string.h>

#include <set>

using namespace std;

typedef long long LL;
constexpr int N = 200005;

int n;
LL p[N], s[N], v[N], res[N];
int l[N], r[N];
struct cmp {
  bool operator()(int x, int y) { return v[x] != v[y] ? v[x] < v[y] : x < y; }
};
set<int, cmp> q;

LL calc(LL d, LL s, int k) {
  LL t = (2 * d - 1) / s;
  if (k) {
    t += !(t & 1);
  } else {
    t += 1;
    t += (t & 1);
  }
  return t;
}

const long long INF = 1e18;
int main() {
  int task;
  for (scanf("%d", &task); task--;) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", p + i);
    }
    for (int i = 0; i < n; ++i) {
      scanf("%lld", s + i);
    }
    l[0] = -1;
    r[n - 1] = n;
    for (int i = 1; i < n; ++i) {
      l[i] = i - 1, r[i - 1] = i;
      v[i] = calc(p[i] - p[i - 1], s[i - 1] + s[i], i & 1);
      q.emplace(i);
    }
    while (q.size()) {
      int x = *q.begin();
      q.erase(x);
      int y = l[x];
      q.erase(y);
      res[x] = res[y] = v[x];
      r[l[y]] = r[x];
      l[r[x]] = l[y];
      if (r[x] == n) {
        continue;
      }
      q.erase(r[x]);
      if (l[y] != -1)
        v[r[x]] = calc(p[r[x]] - p[l[y]], s[r[x]] + s[l[y]], r[x] & 1);
      else
        v[r[x]] = INF;
      q.emplace(r[x]);
    }
    for (int x = 0; x < n; ++x) {
      printf("%lld%c", res[x], x != n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}

/*

1
4
0 1 2 123456
1 1 1 1

*/
