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
  read(v.first, v.second);
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

const int N = 5005;
int n, a[N];
int vis[N];
int mex[N][N];
int d[N];
int pos[N];
int cnt[N][N];

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < n; i++) {
    memset(vis, 0, sizeof vis);
    int mx = 0;
    for (int j = i; j < n; j++) {
      vis[a[j]] = 1;
      while (vis[mx]) {
        mx += 1;
      }
      mex[i][j] = mx;
    }
  }
  for (int i = 0; i <= n; i++) {
    pos[i] = 0;
    for (int j = 0; j < n; j++) {
      cnt[i][j] = 0;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      cnt[mex[i][j]][j] += 1;
    }
  }
  for (int i = 0; i < N; i++) {
    d[i] = n;
  }
  memset(vis, 0, sizeof vis);
  pqg<pii> q;
  d[0] = -1;
  int l = 0;
  q.emplace(-1, 0);
  while (!q.empty()) {
    auto [dis, u] = q.top();
    q.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = 1;
    while (l <= dis) {
      for (int r = l; r < n; r++) {
        cnt[mex[l][r]][r] -= 1;
      }
      l += 1;
    }
    for (int i = 0; i <= n; i++) {
      int &p = pos[i];
      while (p < n && !cnt[i][p])
        p += 1;
      if (d[u ^ i] > p) {
        d[u ^ i] = p;
        q.emplace(d[u ^ i], u ^ i);
      }
    }
  }

  for (int i = N - 1; i >= 0; i--) {
    if (d[i] < n) {
      cout << i << "\n";
      return;
    }
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