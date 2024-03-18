#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (int i = 0; i < a; i++)
#define rep2(i, a) for (int i = 0; i < a; i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
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

template <class... T> void read() {}
template <class T> void read(T &x) { cin >> x; }

template <class T, class S> void read(pair<T, S> &v) {
  cin >> v.first >> v.second;
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

int n, t;
int id(int x, int y) {
  return x * 101 + y;
}
int id(pii a) {
  return id(a.first, a.second);
}
pair<int, int> h, e;
vc<pii> g[101 * 2];
int dis[101 * 101];
int vis[101 * 101];
pii pre[101 * 101];
int row[101];
int col[101];

void solve() {
  read(n, t);
  read(h, e);
  for (int i = 0; i < n; i++) {
    int x, y;
    read(x, y);
    g[x].pb(y + 101, i + 1);
    g[y + 101].pb(x, i + 1);
    row[x] = i + 1;
    col[y] = i + 1;
  }
  memset(dis, 0x3f, sizeof dis);
  queue<int> q[2];
  q[0].emplace(id(h));
  dis[id(h)] = 0;
  while (!q[0].empty() || !q[1].empty()) {
    int u0 = -1, u1 = -1;
    if (!q[0].empty()) {
      u0 = q[0].front();
    }
    if (!q[1].empty()) {
      u1 = q[1].front();
    }
    int u = -1;
    if (u0 == -1) {
      u = u1;
      q[1].pop();
    } else if (u1 == -1) {
      u = u0;
      q[0].pop();
    } else {
      if (dis[u0] <= dis[u1]) {
        u = u0;
        q[0].pop();
      } else {
        u = u1;
        q[1].pop();
      }
    }
    if (vis[u] == 1) {
      continue;
    }
    vis[u] = 1;
    int x = u / 101;
    int y = u % 101;
    for (int dx : {-1, 1}) {
      if (0 <= x + dx && x + dx <= 100) {
        int v = id(x + dx, y);
        if (dis[v] > dis[u] + 1) {
          dis[v] = dis[u] + 1;
          pre[v] = pii(u, 0);
          q[0].emplace(v);
        }
      }
    }
    for (int dy : {-1, 1}) {
      if (0 <= y + dy && y + dy <= 100) {
        int v = id(x, y + dy);
        if (dis[v] > dis[u] + 1) {
          dis[v] = dis[u] + 1;
          pre[v] = pii(u, 0);
          q[0].emplace(v);
        }
      }
    }
    if (row[x]) {
      for (int Y = 0; Y <= 100; Y++) {
        int v = id(x, Y);
        if (dis[v] > dis[u] + t) {
          dis[v] = dis[u] + t;
          pre[v] = pii(u, row[x]);
          q[1].emplace(v);
        }
      }
    }
    if (col[y]) {
      for (int X = 0; X <= 100; X++) {
        int v = id(X, y);
        if (dis[v] > dis[u] + t) {
          dis[v] = dis[u] + t;
          pre[v] = pii(u, col[y]);
          q[1].emplace(v);
        }
      }
    }
    for (auto [Y, i] : g[x]) {
      Y -= 101;
      for (int x = 0; x <= 100; x++) {
        int v = id(x, Y);
        if (dis[v] > dis[u] + t) {
          dis[v] = dis[u] + t;
          pre[v] = pii(u, i);
          q[1].emplace(v);
        }
      }
    }
    for (auto [X, i] : g[y + 101]) {
      for (int y = 0; y <= 100; y++) {
        int v = id(X, y);
        if (dis[v] > dis[u] + t) {
          dis[v] = dis[u] + t;
          pre[v] = pii(u, i);
          q[1].emplace(v);
        }
      }
    }
  }

  double d = sqrt(pow(e.first - h.first, 2) + pow(e.second - h.second, 2));
  double d2 = dis[id(e)];

  if (d < d2) {
    cout << d << "\n";
    cout << 1 << "\n";
    cout << 0 << " " << e.first << " " << e.second << "\n";
  } else {
    cout << d2 << "\n";
    int p = id(e);
    vector<array<int, 3>> ans;
    while (p != id(h)) {
      ans.push_back(array<int, 3>{pre[p].second, p / 101, p % 101});
      p = pre[p].first;
    }
    reverse(all(ans));
    cout << sz(ans) << "\n";
    for (auto [x, y, z] : ans) {
      cout << x << " " << y << " " << z << "\n";
    }
  }
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}