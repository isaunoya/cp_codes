# The 2nd Universal Cup Stage 1: Qingdao, Sep 2-3, 2023

https://contest.ucup.ac/contest/1339

## A.

有 $m$ 个 perfect 和 $n-m$ 个 nonperfect，分别使得连续段最大或者最小。

连续段最大显然是 $m$ 个 perfect 连在一起。

连续段最小的话可以考虑将把 $m$ 拆成 $n-m+1$ 段（$n-m$ 个可以拆分成 $n-m+1$ 段）

所以答案是 $m$ 和 $\lceil \frac{m}{n-m+1}\rceil$。

## B.

每个点的代价是离他最近的一个红点祖先的距离，每次询问选出 $k$ 个点，你可以随意改变一个点的颜色，使得 $\max\{ cost_{v_i} \}$ 最小。

要想要最大值变小，先将 $cost_{v_i}$  排序，然后可以知道选的点一定在 $lca(v_i....v_k)$ 上。

所以每次的答案就是 $\max\{cost{v_{i-1}}, \max\{dep_{v_i} ... dep_{v_k}\} - dep_{lca}\}$。

时间复杂度 $O(n \log n)$。

## C.

总状态数是 $256n$，如果模拟了 $256n$ 步没有走出去，说明一定走了重复的路，也就是走不出去。

## D.

从上往下扫描线。

- 第一问是容易的，记录一下当前行有多少个，然后每次答案加上这个就可以。

- 第二问的话考虑边数不会超过 $K_4$，边数很少，可以直接暴力。

线段树跑了 1.5s，在 pta 上过了（时限 2s）。

用 set 倒是过得很容易。

```cpp
#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
#define pb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  x = x < y ? x : y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  x = x > y ? x : y;
}
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vi r1(k), r2(k), c1(k), c2(k);
  vc<vi> add(n), del(n);
  rp(i, k) {
    cin >> r1[i] >> c1[i] >> r2[i] >> c2[i];
    r1[i]--;
    c1[i]--;
    add[r1[i]].pb(i);
    if (r2[i] < n) {
      del[r2[i]].pb(i);
    }
  }

  vi f(k);
  iota(all(f), 0);
  auto find = [&](int x) {
    while (x != f[x]) {
      x = f[x] = f[f[x]];
    }
    return x;
  };


  ll ans = 0;
  int comp = 0;
  int width = 0;
  auto merge = [&](int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      f[y] = x;
      comp--;
    }
  };

  set<array<int, 3>> s;

  for (int x = 0; x < n; x++) {
    for (int i : add[x]) {
      auto it = s.lower_bound({c1[i], 0, 0});
      if (it != s.begin()) {
        it--;
      }
      while (it != s.end() && (*it)[0] < c2[i]) {
        if ((*it)[1] > c1[i]) {
          merge((*it)[2], i);
        }
        it++;
      }
    }
    for (int i : del[x]) {
      width -= c2[i] - c1[i];
      s.erase({c1[i], c2[i], i});
    }
    for (int i : add[x]) {
      auto it = s.insert({c1[i], c2[i], i}).first;
      if (it != s.begin()) {
        auto prv = prev(it);
        if ((*prv)[1] == c1[i]) {
          merge((*prv)[2], i);
        }
      }
      auto nxt = next(it);
      if (nxt != s.end()) {
        if ((*nxt)[0] == c2[i]) {
          merge((*nxt)[2], i);
        }
      }
      width += c2[i] - c1[i];
      comp++;
    }
    ans += width;
    cout << ans << " " << comp << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

## E.

https://www.luogu.com.cn/blog/jiangly/the-2nd-universal-cup-stage-1-qingdao

## F.

题目里所说的划分，$V = A + B$，$A$ 是团，$B$ 是最大独立集。

首先先找到一个合法的 $|A|$ 最大的团：将度数从大到小排序，贪心的加入 $A$，如果加入之后还是团那么就加入，就可以得到一个合法的答案，然后来计算数量，注意到其他的最大团只能是 $A$ 替换掉一个点，如果可以替换两个点，就说明新加的两个点之间有边，但他们本身在 $B$ 中，矛盾。

独立集的部分取补图之后是完全一致的。

当然也可以在原图上操作。

首先如果 $A$ 中有的点只有 $|A|-1$ 条边，说明他是可以塞到独立集里面的，最多删掉一个（因为团的性质）。

然后可以知道独立集最大是 $|B|$，类似的求出来就好了。

```cpp
#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
#define pb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  x = x < y ? x : y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  x = x > y ? x : y;
}
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> adj(n);
  rp(i, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    adj[x].pb(y);
    adj[y].pb(x);
  }
  vi p(n);
  iota(all(p), 0);
  sort(all(p), [&](auto x, auto y) { return sz(adj[x]) > sz(adj[y]); });
  vi vis(n);
  int cnt = 0;
  for (auto x : p) {
    int res = 0;
    for (auto y : adj[x]) {
      if (vis[y]) {
        res += 1;
      }
    }
    if (res == cnt) {
      cnt += 1;
      vis[x] = 1;
    }
  }
  int ans1 = 1;
  int ans2 = 1;
  rp(i, n) {
    if (!vis[i] && sz(adj[i]) == cnt - 1) {
      ans1 += 1;
    }
  }
  rp(i, n) {
    if (vis[i] && sz(adj[i]) == cnt - 1) {
      cnt--;
      vis[i] = 0;
    }
  }
  rp(i, n) {
    if (vis[i] && sz(adj[i]) == cnt) {
      ans2 += 1;
    }
  }
  cout << ans1 << " " << ans2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

## G.

套个 jiangly 的做法。

就是，可以把 a 经过处理变成一个排列，不影响正确性。

具体的：

```cpp
std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    std::vector<int> o(n);
    std::iota(o.begin(), o.end(), 0);
    std::sort(o.begin(), o.end(),
        [&](int i, int j) {
            return a[i] < a[j] || (a[i] == a[j] && i < j);
        });
    for (int i = 0; i < n; i++) {
        a[o[i]] = i;
    }
```

然后把每一段的逆序对数都放到 multiset 里，每次删掉一个 p 之后，直接把下标在 $[l,p)$ 和 $(p,r]$ 线段树分裂出来，并打上 tag 维护每一个段的逆序对数，答案就是 multiset 里最大的元素。

## H.

考虑第 i 个红绿灯的贡献即可。

## I.

https://blog.cubercsl.site/post/kuririn-miracle/

## J.

给六个数字 a, b, c, d, t, v，给一盏灯，每隔 v+0.5 s 就会熄灭，每隔 A 秒可以拍 B 下，每隔 C 秒可以拍 D 下，如果灯是灭的，就让灯亮，如果灯是亮的，就让分数+1，并将灯重新设置成 v+0.5 s熄灭。

首先可以算出来拍了多少下灯，是 $(t/a) \times b + (t/c) \times d + b + d$，然后计算一下要拍亮几次灯就可以了。

```cpp
void solve() {
  ll a, b, c, d, v, t;
  cin >> a >> b >> c >> d >> v >> t;
  vc<ll> V;
  ll l = lcm(a, c);
  V.pb(0);
  for (ll i = a; i < l; i += a)
    V.pb(i);
  for (ll i = c; i <= l; i += c)
    V.pb(i);
  sort(all(V));
  ll tmp = 0;
  for (int i = 1; i < V.size(); i++) {
    if (V[i] - V[i - 1] > v) {
      tmp += 1;
    }
  }
  ll ans = (t / a) * b + (t / c) * d + b + d - 1;
  ll cur = t / l;
  ans = ans - cur * tmp;
  t %= l;
  for (int i = 1; V[i] <= t; i++) {
    if (V[i] - V[i - 1] > v) {
      ans -= 1;
    }
  }
  cout << ans << "\n";
}
```

## K.

记录最高位。