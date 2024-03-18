#include <bits/stdc++.h>
#include <queue>
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

int ST[18][200000];
struct heap {
  priority_queue<int> p, q;
  void emplace(int x) { p.emplace(x); }
  void pop(int x) { q.emplace(x); }
  int top() {
    while (!p.empty() && !q.empty() && p.top() == q.top())
      p.pop(), q.pop();
    assert(!p.empty());
    return p.top();
  }
};

void solve() {
  int n;
  cin >> n;
  vi a(n), b(n);
  rep(i, n) cin >> a[i];
  rep(i, n) cin >> b[i];

  int ok = 1;
  rep(i, n) ok &= (a[i] <= b[i]);
  if (!ok) {
    cout << "NO\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    ST[0][i] = b[i];
  }
  for (int j = 1; j < 18; j++) {
    for (int i = 0; i + (1 << j - 1) < n; i++) {
      ST[j][i] = min(ST[j - 1][i], ST[j - 1][i + (1 << j - 1)]);
    }
  }
  auto query = [&](int l, int r) {
    r += 1;
    int L = __lg(r - l);
    return min(ST[L][l], ST[L][r - (1 << L)]);
  };

  vi L(n), R(n);
  rep(i, n) {
    // min_left
    {
      int l = -1, r = i;
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (query(m, i) >= a[i])
          r = m;
        else
          l = m;
      }
      L[i] = r;
    }
    // max_right
    {
      int l = i, r = n;
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (query(i, m) >= a[i])
          l = m;
        else
          r = m;
      }
      R[i] = l;
    }
  }
  // debug(L, R);

  vc<vi> add(n + 1), del(n + 1);
  heap w;
  vi stk;
  rep(i, n) {
    while (!stk.empty() && a[stk.back()] <= a[i])
      stk.pop_back();
    // a[stk.back()]>a[i]
    if (!stk.empty())
      cmax(L[i], stk.back() + 1);
    stk.emplace_back(i);
  }
  stk.clear();
  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && a[stk.back()] <= a[i])
      stk.pop_back();
    if (!stk.empty())
      cmin(R[i], stk.back() - 1);
    stk.emplace_back(i);
  }

  rep(i, n) add[L[i]].pb(a[i]), del[R[i] + 1].pb(a[i]);
  rep(i, n) {
    for (auto v : add[i])
      w.emplace(v);
    for (auto v : del[i])
      w.pop(v);
    // debug(w.top());
    if (w.top() != b[i]) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
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