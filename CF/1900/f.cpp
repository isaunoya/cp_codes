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
  int n, q;
  cin >> n >> q;
  vi A(n);
  rep(i, n) cin >> A[i];
  vi a(n);
  iota(all(a), 0);
  auto solve = [&](const vi &a, int op) {
    vi b;
    int n = a.size();
    rep(j, n) {
      int i = a[j];
      if ([&]() {
            int x = (j == 0) ? 1 : ((A[i] < A[a[j - 1]]) ^ op);
            int y = (j + 1 == n) ? 1 : ((A[i] < A[a[j + 1]]) ^ op);
            return x && y;
          }()) {
        b.pb(i);
      }
    }
    return b;
  };
  vc<vi> t = {a};
  for (int i = 0; sz(t[i]) > 1; i++) {
    t.pb(solve(t[i], i % 2));
  }
  auto get = [&](auto &get, int l, int r, int i, vi L, vi R) {
    int posl = lower_bound(all(t[i]), l) - t[i].begin();
    int posr = lower_bound(all(t[i]), r) - t[i].begin();
    if (posr - posl <= 4) {
      vi res = L;
      res.insert(res.end(), t[i].begin() + posl, t[i].begin() + posr);
      res.insert(res.end(), all(R));
      int j = i % 2;
      while (sz(res) > 1) {
        res = solve(res, j);
        j ^= 1;
      }
      return res[0];
    }
    L.insert(L.end(), t[i][posl]);
    L.insert(L.end(), t[i][posl + 1]);
    R.insert(R.begin(), t[i][posr - 1]);
    R.insert(R.begin(), t[i][posr - 2]);
    L = solve(L, i % 2);
    R = solve(R, i % 2);
    if (L.back() == t[i][posl + 1])
      L.pop_back();
    if (R[0] == t[i][posr - 2])
      R.erase(R.begin());
    return get(get, t[i][posl + 1], t[i][posr - 1], i + 1, L, R);
  };
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l;
    cout << A[get(get, l, r, 0, {}, {})] << "\n";
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