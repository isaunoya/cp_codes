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

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  string t;

  vc<vi> p(26);

  rep(i, n) {
    int x = s[i] - 'a';
    p[x].pb(i);
  }

  vi cnt(26);
  int mx = -1;
  for (int i = 25; i >= 0; i--) {
    for (int j : p[i]) {
      if (j > mx) {
        t += s[j];
        s[j] = 0;
        mx = j;
        cnt[i] += 1;
      }
    }
  }

  int cost = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 0) {
      s[i] = t.back();
      t.pop_back();
      int w = 0;
      rep(j, 26) if (cnt[j]) w += 1;
      if (w > 1) cost += 1;
      cnt[s[i] - 'a'] -= 1;
    }
  }
  if (is_sorted(all(s))) {
    cout << cost << "\n";
  } else {
    cout << -1 << "\n";
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