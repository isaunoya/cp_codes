#include <bits/stdc++.h>
#include <cstring>
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

const int N = 5e5 + 5;
ll m[N * 4], t[N * 4];
void pull(int p) { m[p] = max(m[p * 2], m[p * 2 + 1]); }
void push(int p, const ll &v) {
  m[p] += v;
  t[p] += v;
}
void down(int p) {
  if (t[p]) {
    push(p * 2, t[p]);
    push(p * 2 + 1, t[p]);
    t[p] = 0;
  }
}
void upd(int l, int r, int p, const int &x, const ll &v) {
  if (l == r) {
    m[p] = v;
    return;
  }
  down(p);
  int m = (l + r) / 2;
  if (l <= m) {
    upd(l, m, p * 2, x, v);
  } else {
    upd(m + 1, r, p * 2 + 1, x, v);
  }
  pull(p);
}
void add(int ql, int qr, int l, int r, int p, const ll &v) {
  if (ql <= l && r <= qr) {
    push(p, v);
    return;
  }
  down(p);
  int m = (l + r) / 2;
  if (ql <= m) {
    add(ql, qr, l, m, p * 2, v);
  }
  if (qr > m) {
    add(ql, qr, m + 1, r, p * 2 + 1, v);
  }
  pull(p);
}

void solve() {
  int N;
  cin >> N;
  vc<ll> A(N), B(N);
  rep(i, N) cin >> A[i];
  rep(i, N) cin >> B[i];
  vc<ll> dp(N + 1, -lnf);
  rep(i, N * 4) m[i] = -lnf;
  upd(0, N, 1, 0, dp[0] = 0);
  vector<int> stk{-1};
  rep(i, N) {
    while (stk.size() > 1 && A[stk.back()] > A[i]) {
      add(stk[stk.size() - 2] + 1, stk.back(), 0, N, 1, -B[stk.back()]);
      stk.pop_back();
    }
    add(stk.back() + 1, i, 0, N, 1, B[i]);
    stk.emplace_back(i);
    dp[i + 1] = m[1];
    add(i + 1, i + 1, 0, N, 1, dp[i + 1] + lnf);
  }
  cout << dp[N] << "\n";
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