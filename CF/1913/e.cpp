#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (auto i = 0; i < a; i++)
#define rep2(i, a) for (auto i = 0; i < a; i++)
#define rep3(i, a, b) for (auto i = a; i < b; i++)
#define rep4(i, a, b, c) for (auto i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

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
#define fi first
#define se second

using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
namespace Flow {
int S, T;
void Set(int _S, int _T) { S = _S, T = _T; }
struct Edge_t {
  int v, nxt, w, cost;
  Edge_t(int V = 0, int Nxt = 0, int W = 0, int Cost = 0) {
    v = V, nxt = Nxt, w = W, cost = Cost;
  }
};
std::vector<Edge_t> e(2);
std::vector<int> head;
void add(int u, int v, int w, int cost) {
  if (u >= (int)head.size()) {
    head.resize(u + 127);
  }
  e.emplace_back(v, head[u], w, cost);
  head[u] = (int)e.size() - 1;
}
void addedge(int u, int v, int w, int cost) {
  add(u, v, w, cost);
  add(v, u, 0, -cost);
}
constexpr int inf = 1e9;
std::queue<int> q;
std::vector<int> dep;
std::vector<int> cur;
std::vector<bool> inq;
bool bfs() {
  dep.assign(head.size(), inf);
  inq.assign(head.size(), false);
  cur = head;
  q.emplace(S), dep[S] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = false;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (e[i].w && dep[v] > dep[u] + e[i].cost) {
        dep[v] = dep[u] + e[i].cost;
        if (!inq[v]) {
          inq[v] = true;
          q.emplace(v);
        }
      }
    }
  }
  return dep[T] < inf;
}
int dfs(int u, int flow) {
  if (!flow) {
    return 0;
  } else if (u == T) {
    return flow;
  } else {
    inq[u] = true;
    int f = 0;
    for (int &i = cur[u], rf; i; i = e[i].nxt) {
      int v = e[i].v;
      if (!inq[v] && dep[v] == dep[u] + e[i].cost &&
          (rf = dfs(v, std::min(flow, e[i].w)))) {
        flow -= rf, f += rf;
        e[i].w -= rf, e[i ^ 1].w += rf;
        if (flow == 0) {
          return f;
        }
      }
    }
    return f;
  }
}
std::pair<int, int> dinic() {
  int ans = 0, res = 0;
  while (bfs()) {
    int tmp = dfs(S, inf);
    ans += tmp;
    res += dep[T] * tmp;
  }
  return std::make_pair(ans, res);
}
} // namespace Flow
int a[60][60];
int A[60], B[60];
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  for (int i = 0; i < m; i++) {
    cin >> B[i];
  }

  int S, T;
  Flow::Set(S = n * m * 2 + (n + m) * 2, T = n * m * 2 + (n + m) * 2 + 1);
  for (int i = 0; i < n; i++) {
    Flow::addedge(S, i, A[i], 0);
  }
  for (int i = 0; i < n; i++) {
    Flow::addedge(S, i + n, m - A[i], 0);
  }
  for (int i = 0; i < m; i++) {
    Flow::addedge(i + n * 2, T, B[i], 0);
  }
  for (int i = 0; i < m; i++) {
    Flow::addedge(i + m + n * 2, T, n - B[i], 0);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int v0 = (n + m) * 2 + i * m + j;
      int v1 = v0 + n * m;
      Flow::addedge(i + n, v0, 1, a[i][j] == 1);
      Flow::addedge(v0, j + m + n * 2, 1, 0);
      Flow::addedge(i, v1, 1, a[i][j] == 0);
      Flow::addedge(v1, j + n * 2, 1, 0);
    }
  }
  auto f = Flow::dinic();
  if (f.first < n * m) {
    cout << -1 << "\n";
  } else
    cout << f.second << "\n";
  return 0;
}
