#include <bits/stdc++.h>
#include <string>
#ifndef LOCAL
#define debug(...) 42
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
#define fi first
#define se second

map<string, int> mp;
int c = 0;
vi g[100];
int f[100];
void solve() {
  int n, m;
  cin >> n >> m;
  memset(f, -1, sizeof f);
  for (int i = 0; i < n; i++) {
    string p;
    cin >> p;
    if (!mp.count(p)) {
      mp[p] = c++;
    }
    int w = mp[p];
    int k;
    cin >> k;
    while (k--) {
      string v;
      cin >> v;
      if (!mp.count(v)) {
        mp[v] = c++;
      }
      int q = mp[v];
      g[w].pb(q);
      f[q] = w;
    }
  }
  int rt = -1;
  rep(i, c) if (f[i] == -1) rt = i;
  vi d(c, -1);
  queue<int> q;
  d[rt] = 0;
  q.emplace(rt);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (d[v] == -1) {
        q.emplace(v);
        d[v] = d[u] + 1;
      }
    }
  }
  while (m--) {
    string a, b;
    cin >> a >> b;
    int A = mp[a];
    int B = mp[b];
    int aa = A, bb = B;
    while (d[aa] > d[bb])
      aa = f[aa];
    while (d[aa] < d[bb])
      bb = f[bb];
    while (aa != bb)
      aa = f[aa], bb = f[bb];
    int C = aa;
    if (A == C || B == C) {
      if (d[A] < d[B]) {
        swap(a, b);
        swap(A, B);
      }
      int w = d[A] - d[C];
      if (w == 1) {
        cout << a << " is the child of " << b << "\n";
      } else {
        w -= 2;
        cout << a << " is the ";
        while (w--)
          cout << "great ";
        cout << "grandchild of " << b << "\n";
      }
    } else {
      int w1 = d[A] - d[C];
      int w2 = d[B] - d[C];
      if (w1 == 1 && w2 == 1) {
        cout << a << " and " << b << " are siblings\n";
      } else {
        // debug(a,b,w1,w2);
        auto id = [&](int x) {
          if (x == 11 || x == 12 || x == 13) {
            cout << x << "th ";
            return;
          }
          if (x % 10 == 1) {
            cout << x << "st ";
            return;
          }
          if (x % 10 == 2) {
            cout << x << "nd ";
            return;
          }
          if (x % 10 == 3) {
            cout << x << "rd ";
            return;
          }
          cout << x << "th ";
        };
        string time = "time";
        if (abs(w1 - w2) >= 2)
          time += "s";
        cout << a << " and " << b << " are ", id(min(w1, w2) - 1),
            cout << "cousins";
        if (w1 - w2)
          cout << ", " << abs(w1 - w2) << " " << time << " removed\n";
        else
          cout << "\n";
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}