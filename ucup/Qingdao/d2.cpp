#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vi r1(k), r2(k), c1(k), c2(k);
  vc<vi> add(n), del(n);
  rp(i, k) {
    cin >> r1[i] >> c1[i] >> r2[i] >> c2[i];
    r1[i]--;
    c1[i]--;
    add[r1[i]].pb(i);
    if (r2[i] < n) {
      del[r2[i]].pb(i);
    }
  }

  vi f(k);
  iota(all(f), 0);
  auto find = [&](int x) {
    while (x != f[x]) {
      x = f[x] = f[f[x]];
    }
    return x;
  };


  ll ans = 0;
  int comp = 0;
  int width = 0;
  auto merge = [&](int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      f[y] = x;
      comp--;
    }
  };

  set<array<int, 3>> s;

  for (int x = 0; x < n; x++) {
    for (int i : add[x]) {
      auto it = s.lower_bound({c1[i], 0, 0});
      if (it != s.begin()) {
        it--;
      }
      while (it != s.end() && (*it)[0] < c2[i]) {
        if ((*it)[1] > c1[i]) {
          merge((*it)[2], i);
        }
        it++;
      }
    }
    for (int i : del[x]) {
      width -= c2[i] - c1[i];
      s.erase({c1[i], c2[i], i});
    }
    for (int i : add[x]) {
      auto it = s.insert({c1[i], c2[i], i}).first;
      if (it != s.begin()) {
        auto prv = prev(it);
        if ((*prv)[1] == c1[i]) {
          merge((*prv)[2], i);
        }
      }
      auto nxt = next(it);
      if (nxt != s.end()) {
        if ((*nxt)[0] == c2[i]) {
          merge((*nxt)[2], i);
        }
      }
      width += c2[i] - c1[i];
      comp++;
    }
    ans += width;
    cout << ans << " " << comp << "\n";
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