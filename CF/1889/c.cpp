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
  int n, m, k;
  cin >> n >> m >> k;

  vc<vc<pii>> op(n);
  rep(i, m) {
    int l, r;
    cin >> l >> r;
    --l;
    op[l].pb(i, 1);
    if (r < n) {
      op[r].pb(i, -1);
    }
  }

  set<int> cur;
  int dry = 0;
  vi single(m);
  map<pii, int> pair;
  rep(i, n) {
    for (auto [x, y] : op[i]) {
      if (y > 0) {
        cur.emplace(x);
      } else {
        cur.erase(x);
      }
    }
    if (sz(cur) <= 2) {
      if (sz(cur) == 0) {
        dry += 1;
      } else if (sz(cur) == 1) {
        single[*cur.begin()] += 1;
      } else {
        int w = *cur.begin();
        int z = *(++cur.begin());
        pair[pii(w, z)] += 1;
      }
    }
  }
  auto w = single;

  int mx = 0;
  {
    sort(all(w));
    reverse(all(w));
    cmax(mx, w[0] + w[1]);
  }

  for (auto [t, z] : pair) {
    auto [x, y] = t;
    cmax(mx, z + single[x] + single[y]);
  }

  cout << dry + mx << "\n";
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