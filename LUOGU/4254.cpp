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

const int B = 1000;

template <class P, class V> struct convex_hull {
  vc<P> p, p2;
  void clear() { p.clear(); }
  void pu(const P &value) {
    p2.pb(value);
    if (p2.size() == B)
      init();
  }

  V cross(const P &x, const P &y) {
    return x.first * y.second - x.second * y.first;
  }

  void init() {
    for (const auto &value : p2) {
      p.pb(value);
    }
    p2.clear();
    sort(all(p), greater<P>());
    vc<P> t;
    int sz = 0;
    auto getcross = [&](const P &x, const P &y, const P &z) {
      return cross(P(y.fi - x.fi, y.se - x.se), P(z.fi - y.fi, z.se - y.se));
    };
    for (const auto &value : p) {
      while (sz >= 2 && getcross(t[sz - 2], t[sz - 1], value) <= 0) {
        t.pop_back();
        sz--;
      }
      t.pb(value);
      sz++;
    }
    p.swap(t);
    debug(p);
  }
  V get(const V &x) {
    auto evalueate = [&](int i) {
      if (i < 0 || i >= p.size()) {
        return (V)0;
      }
      return (V)x * p[i].first + p[i].second;
    };
    int l = -1, r = p.size();
    while (r - l > 2) {
      int m1 = (l + r) / 2;
      int m2 = m1 + 1;
      if (evalueate(m1) > evalueate(m2)) {
        r = m2;
      } else {
        l = m1;
      }
    }
    V ans = 0;
    for (int i = l; i <= r; i++) {
      cmax(ans, evalueate(i));
    }
    for (auto &[k, b] : p2) {
      cmax(ans, (V)x * k + b);
    }
    return ans;
  }
};

void solve() {
  int N;
  cin >> N;
  convex_hull<pair<double, double>, double> ch;
  while (N--) {
    string s;
    cin >> s;
    if (s == "Project") {
      double x, y;
      cin >> x >> y;
      ch.pu(pair<double, double>(y, x - y));
    } else {
      double x;
      cin >> x;
      debug(ch.get(x));
      cout << (int)ch.get(x) / 100 << "\n";
    }
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