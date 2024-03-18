#include <bits/stdc++.h>
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

const int P = 1e9 + 7;
const int N = 2e5 + 5;
int ch[N][26];
int cnt = 1;
int hav[N];
ll w[N];
int fail[N];

void solve() {
  int n, m;
  cin >> n >> m;
  rep(i, n) {
    string s;
    cin >> s;
    int p = 1;
    for (char x : s) {
      int c = x - 'a';
      if (!ch[p][c]) {
        ch[p][c] = ++cnt;
      }
      p = ch[p][c];
    }
    hav[p] += 1;
    w[p] += sz(s);
  }
  queue<int> q;
  rep(i, 26) if (ch[1][i]) fail[ch[1][i]] = 1, q.emplace(ch[1][i]);
  else ch[1][i] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    rep(i, 26) {
      if (ch[u][i])
        fail[ch[u][i]] = ch[fail[u]][i], q.emplace(ch[u][i]);
      else
        ch[u][i] = ch[fail[u]][i];
    }
  }
  vc<vi> g(cnt + 1);
  debug(g);
  rep(i, 2, cnt + 1) g[fail[i]].pb(i);
  auto dfs = [&](auto &self, int u) -> void {
    debug(u);
    for (auto v : g[u]) {
      w[v] += w[u];
      hav[v] += hav[u];
      self(self, v);
    }
  };
  dfs(dfs, 1);

  while (m--) {
    string t;
    cin >> t;
    int l = sz(t);
    int p = 1;
    ll ans = 0;
    for (int i = 0; i < l; i++) {
      int c = t[i] - 'a';
      p = ch[p][c];
      ll val = 1ll * hav[p] * (i + 2) - w[p];
      val %= P;
      ans += 1ll * val * (l - i) % P;
      if (ans >= P) {
        ans -= P;
      }
    }
    cout << ans << "\n";
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