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

const int N = 2e6 + 5;
int ch[N][26], cnt = 1;
int siz[N];
int suf[27];
int ed[N];
void solve() {
  int n, k;
  cin >> n >> k;
  rep(i, cnt + 1) memset(ch[i], 0, sizeof ch[i]), siz[i] = 0, ed[i] = 0;
  cnt = 1;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int p = 1;
    for (auto cc : s) {
      int c = cc - 'a';
      if (!ch[p][c]) ch[p][c] = ++cnt;
      p = ch[p][c];
      siz[p] += 1;
    }
    ed[p] += 1;
  }
  string ans = "";
  auto dfs = [&](auto &dfs, int u) {
    rep(i, 26) suf[i] = 0;
    for (int j = 25; j >= 0; j--) {
      suf[j] = suf[j + 1];
      int s = siz[ch[u][j]];
      if (s >= 1) {
        suf[j] += 1;
      }
    }
    if (ed[u] + suf[0] >= k) {
      return;
    }
    int ned = 0;
    rep(i, 26) if (ch[u][i]) {
      int s = siz[ch[u][i]];
      if (s > 1 && ned + s + ed[u] + suf[i + 1] >= k) {
        k -= ned + suf[i + 1] + ed[u];
        ans += char(i + 'a');
        dfs(dfs, ch[u][i]);
        return;
      }
      ned += s;
    }
  };

  dfs(dfs, 1);
  if (ans.empty()) {
    cout << "EMPTY\n";
  } else {
    cout << ans << "\n";
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