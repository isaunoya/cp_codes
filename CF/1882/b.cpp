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

void solve() {
  int N;
  cin >> N;
  vc<vi> A(N);
  vc<vi> B(50);
  rep(i, N) {
    int k;
    cin >> k;
    A[i].resize(k);
    rep(j, k) {
      cin >> A[i][j];
      --A[i][j];
      B[A[i][j]].pb(i);
    }
  }
  vi cnt(50);
  rep(i, N) {
    rep(j, A[i].size()) {
      cnt[A[i][j]] += 1;
    }
  }
  int res = 0;
  rep(k, 50) {
    if (B[k].size() == 0) {
      continue;
    }
    for (auto i : B[k]) {
      for (auto j : A[i]) {
        cnt[j] -= 1;
      }
    }
    int ans = 0;
    rep(j, 50) {
      if (cnt[j]) {
        ans += 1;
      }
    }
    cmax(res, ans);
    for (auto i : B[k]) {
      for (auto j : A[i]) {
        cnt[j] += 1;
      }
    }
  }
  cout << res << "\n";
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