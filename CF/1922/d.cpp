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

const int N = 3e5 + 5;
int n, a[N], d[N], l[N], r[N], vis[N];

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  a[n + 1] = 0;
  for (int i = 1; i <= n; i++)
    cin >> d[i];
  for (int i = 1; i <= n; i++) {
    l[i] = i - 1, r[i] = i + 1, vis[i] = 0;
  }

  auto remove = [&](int i) {
    int L = l[i], R = r[i];
    vis[i] = 1;
    r[L] = R, l[R] = L;
  };

  auto good = [&](int i) {
    int L = l[i], R = r[i];
    return !vis[i] && a[L] + a[R] > d[i];
  };

  set<int> die, check;

  for (int i = 1; i <= n; i++) {
    check.emplace(i);
  }

  for (int round = 1; round <= n; round++) {
    for (auto u : check){
      if (good(u)) {
        die.emplace(u);
      }
    }
    check.clear();
    // debug(die);
    cout << die.size() << " \n"[round == n];
    for (auto u : die) {
      remove(u);
      for (auto v : {l[u], r[u]}) {
        if (1 <= v && v <= n) {
          check.emplace(v);
        }
      }
    }
    die.clear();
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