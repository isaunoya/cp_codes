#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define R(i, n) rep(i, 0, n)
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  if (x > y)
    x = y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  if (x < y)
    x = y;
}
using ll = long long;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

void solve() {
  int n;
  cin >> n;
  n *= 2;
  map<pair<int, int>, int> mp;
  R(i, n) {
    int a, b;
    char c;
    cin >> a >> b >> c;
    mp[make_pair(a, b)] += c == '(' ? 1 : -1;
  }
  int m = mp.size();
  vector<pair<pair<int, int>, int>> vp(all(mp));
  ranges::sort(vp, {}, [&](auto p) { return pair(p.first, -p.second); });
  int neg = 0;
  vector<int> sum(m), pos(m);
  R(i, m) {
    if (i) {
      sum[i] = sum[i - 1];
    }
    sum[i] += vp[i].second;
    neg += sum[i] < 0;
    pos[i] = i;
  }
  struct cmp {
    bool operator()(const pair<int, int> &x, const pair<int, int> &y) const {
      return (ll)x.second * y.first < (ll)y.second * x.first;
    }
  };
  using pii = pair<int, int>;
  map<pii, set<int>, cmp> ch;
  R(i, m) {
    R(j, m) {
      int x = vp[j].first.second - vp[i].first.second;
      int y = vp[i].first.first - vp[j].first.first;
      if (x > 0 && y > 0) {
        int d = gcd(x, y);
        x /= d;
        y /= d;
        ch[{x, y}].insert(i);
        ch[{x, y}].insert(j);
      }
    }
  }
  bool ans = (neg == 0);
  for (auto [p, s] : ch) {
    auto [x, y] = p;
    map<ll, vector<int>> mp;
    for (int i : s) {
      ll d = (ll)x * vp[i].first.first + (ll)y * vp[i].first.second;
      mp[d].push_back(i);
    }
    for (auto [_, rg] : mp) {
      int l = pos[rg[0]], r = pos[rg[0]];
      for (int i : rg) {
        cmin(l, pos[i]);
        cmax(r, pos[i]);
      }
      ranges::sort(rg, {}, [&](int i) { return -vp[i].second; });
      assert(r - l + 1 == sz(rg));
      rep(i, l, r + 1) {
        pos[rg[i - l]] = i;
        neg -= sum[i] < 0;
        if (i) {
          sum[i] = sum[i - 1];
        } else {
          sum[i] = 0;
        }
        sum[i] += vp[rg[i - l]].second;
        neg += sum[i] < 0;
      }
      if (neg == 0) {
        ans = true;
      }
    }
    for (auto [_, rg] : mp) {
      int l = pos[rg[0]], r = pos[rg[0]];
      for (int i : rg) {
        cmin(l, pos[i]);
        cmax(r, pos[i]);
      }
      assert(r - l + 1 == sz(rg));
      ranges::sort(rg, {}, [&](int i) { return vp[i].first.second; });
      rep(i, l, r + 1) {
        pos[rg[i - l]] = i;
        neg -= sum[i] < 0;
        if (i) {
          sum[i] = sum[i - 1];
        } else {
          sum[i] = 0;
        }
        sum[i] += vp[rg[i - l]].second;
        neg += sum[i] < 0;
      }
    }
  }
  if (ans) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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