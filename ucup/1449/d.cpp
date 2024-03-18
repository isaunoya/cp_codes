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

int LCP[5005][5005];
void prepare(string s, string t) {
  memset(LCP, 0, sizeof LCP);
  int n = sz(s);
  int m = sz(t);
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      if (s[i] == t[j]) {
        LCP[i][j] = LCP[i + 1][j + 1] + 1;
      }
    }
  }
}

ll res = 0;
int n, m;
string S, T;

int A[5005][5005];
int B[5005][5005];

void slv() {
  prepare(S, S);
  memset(A, 0, sizeof A);
  rep(b, n) rep(a, b) {
    int l = LCP[a][b];
    cmin(l, b - a - 1);
    A[a + 1][b] += 1;
    A[a + l + 1][b] -= 1;
  }
  // S[a:b] = S[b:c]+T[d:e]
  rep(b, n) {
    rep(a, n) { A[a + 1][b] += A[a][b]; }
  }
  prepare(S, T);
  memset(B, 0, sizeof B);
  rep(a, n) rep(b, m) {
    int l = LCP[a][b];
    B[a][a + 1]++;
    B[a][a + l + 1] -= 1;
  }
  rep(a, n) rep(b, n) { B[a][b + 1] += B[a][b]; }

  rep(a, n + 1) rep(b, a + 1, n + 1) { res += 1ll * A[a][b] * B[a][b]; }
}

void solve() {
  cin >> S >> T;
  n = sz(S), m = sz(T);
  prepare(S, T);
  rep(i, n) rep(j, m) { res += LCP[i][j]; }

  slv();

  swap(n, m);
  swap(S, T);
  reverse(all(S));
  reverse(all(T));
  slv();

  cout << res << "\n";
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