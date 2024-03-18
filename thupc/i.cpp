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

int a[500005];
int cnt[500005];
int ap[500005], ad[500005];
int f[500005];
int sz[1000005], w;

void solve() {
  int n = 500000;
  // cin >> n;
  vector<int> b;
  for (int i = 1; i <= n; i++) {
    // char c;
    // cin >> c;
    // if (c == '1')
    if (rng() % 100)
      b.push_back(i);
  }
  vc<array<int, 3>> ans;
  auto solve = [&](auto &solve, const vector<int> &b) -> int {
    int n = b.size();
    if (n == 1) {
      ans.emplace_back(array<int, 3>{1, b[0], 0});
      return ans.size();
    } else if (n <= 512) {
      int v = 0;
      rep(i, n) rep(j, i + 1, n) {
        int d = b[j] - b[i];
        ++cnt[d];
        if (cnt[d] > cnt[v]) {
          v = d;
        }
      }
      rep(i, n) rep(j, i + 1, n) {
        int d = b[j] - b[i];
        cnt[d] = 0;
      }
      if (v == 0) {
        int m = n / 2;
        ans.emplace_back(array<int, 3>{
            2, solve(solve, vector<int>(b.begin(), b.begin() + m)),
            solve(solve, vector<int>(b.begin() + m, b.end()))});
        return ans.size();
      }
      rep(i, n) ap[b[i]] = 1;
      int mn = b[0];
      int mx = b.back();
      vector<int> c, d;
      for (int i = 0; i < n; i++)
        if (b[i] - v >= mn && ad[b[i] - v]) {
          continue;
        } else if (b[i] + v <= mx && ap[b[i] + v]) {
          ad[b[i]] = 1;
          c.push_back(b[i]);
        } else {
          d.push_back(b[i]);
        }
      rep(i, n) ap[b[i]] = ad[b[i]] = 0;
      if (c.empty()) {
        return solve(solve, d);
      } else if (d.empty()) {
        int lc = solve(solve, c);
        ans.emplace_back(array<int, 3>{3, lc, v});
        int lc_v = ans.size();
        ans.emplace_back(array<int, 3>{2, lc, lc_v});
        int lc_all = ans.size();  
        return lc_all;
      } else {
        int lc = solve(solve, c);
        int rc = solve(solve, d);
        int way1 = n - d.size();
        int way2 = (c.size() + d.size());
        ans.emplace_back(array<int, 3>{3, lc, v});
        int lc_v = ans.size();
        if (way1 < way2) {
          ans.emplace_back(array<int, 3>{2, lc, lc_v});
          int lc_all = ans.size();
          ans.emplace_back(array<int, 3>{2, lc_all, rc}); 
        } else {
          ans.emplace_back(array<int, 3>{2, lc, rc});
          int lc_rc = ans.size();
          ans.emplace_back(array<int, 3>{2, lc_rc, lc_v});
        }
        return ans.size();
      }
    } else {
      int m = b.size() / 2;
      ans.emplace_back(
          array<int, 3>{2, solve(solve, vector<int>(b.begin(), b.begin() + m)),
                        solve(solve, vector<int>(b.begin() + m, b.end()))});
      return ans.size();
    }
  };
  solve(solve, b);
  cout << sz(ans) << "\n";
  for (auto p : ans) {
    w += 1;
    if (p[0] == 1) {
      cout << p[0] << " " << p[1] << "\n";
      sz[w] = 1;
    } else if (p[0] == 2) {
      cout << p[0] << " " << p[1] << " " << p[2] << "\n";
      sz[w] = sz[p[1]] + sz[p[2]];
    } else if (p[0] == 3) {
      cout << p[0] << " " << p[1] << " " << p[2] << "\n";
      sz[w] = sz[p[1]];
    }
  }

  int cost = 0;
  for (int i = 1; i <= w; i++) cost += sz[i];
  debug(cost, f[n]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  f[1] = 1;
  for (int i = 2; i <= 500000; i++) {
    int m = i / 2;
    f[i] = i + f[m] + f[i - m];
  }
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}