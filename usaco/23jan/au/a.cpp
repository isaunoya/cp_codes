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

int cnt;

const int N = 262144;
struct Node {
  int l, r;
  char c;
  ll sz;
} t[N];

int rt[26];

void dfs(int p, ll l, ll r) {
  if (r <= 0) {
    return;
  }
  if (l > t[p].sz) {
    return;
  }
  if (t[p].c == '#') {
    dfs(t[p].l, l, r);
    ll s = t[t[p].l].sz;
    dfs(t[p].r, l - s, r - s);
  } else {
    cout << t[p].c;
  }
}

void solve() {
  ll l, r, n;
  cin >> l >> r >> n;
  rep(26) {
    int cur = ++cnt;
    t[cur] = {0, 0, char('a' + i), 1};
    rt[i] = cur;
  }

  vc<char> C(n);
  vc<string> S(n);
  rep(n) cin >> C[i] >> S[i];
  reverse(all(S));
  reverse(all(C));
  rep(n) {
    char c = C[i];

    string s = S[i];

    int cur = 0;
    for (auto x : s) {
      if (!cur) {
        cur = rt[x - 'a'];
      } else {
        int id = ++cnt;
        t[id] = {cur, rt[x - 'a'], '#', min(lnf, t[cur].sz + t[rt[x - 'a']].sz)};
        cur = id;
      }
    }

    rt[c - 'a'] = cur;
  }

  // debug(rt[0]);
  dfs(rt[0], l, r);
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