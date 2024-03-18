#include <bits/stdc++.h>
#define int long long
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

void solve() {
  int n, x1;
  cin >> n >> x1;

  vc<pii> neg;
  vc<pii> pos;
  vi t;
  rep(i, n) {
    int y1, y2, x2;
    cin >> y1 >> y2 >> x2;
    t.pb(y1);
    t.pb(y2);
    neg.pb(x2, y2);
    pos.pb(x2, y1);
  }

  vi s;
  int cnt_neg = 0;
  int cnt_pos = 0;
  rep(i, n * 4) {
    int x;
    cin >> x;
    s.pb(x);
    if (x < 0) {
      cnt_neg += 1;
    }
    if (x > 0) {
      cnt_pos += 1;
    }
  }
  if (min(cnt_neg, cnt_pos) < n) {
    cout << "-1\n";
    return;
  }

  vi v0, v1;
  for (auto x : s) {
    if (x < 0) {
      v0.pb(x);
    } else {
      v1.pb(x);
    }
  }
  sort(all(v0)), reverse(all(v0));
  sort(all(v1));
  vi rem;
  sort(all(t));
  rep(i, n, cnt_neg) rem.pb(v0[i]);
  rep(i, n, cnt_pos) rem.pb(v1[i]);
  sort(all(rem));

  v0.resize(n);
  v1.resize(n);
  // debug(t, rem);
  ll hi = -lnf, lo = lnf;
  rep(i, n * 2) {
    int x = x1;
    int y = t[i];
    int cur = y - x * rem[i];
    cmax(hi, cur);
    cmin(lo, cur);
  }

  {
    int l = -lnf, r = lnf;

    auto check_neg = [&](int t) {
      multiset<int> st{0, lnf};
      rep(i, n) st.emplace(-v0[i]);
      for (auto [x, y] : neg) {
        // y - x * k <= t
        // x * (-k) <= t - y
        ll w = t - y;
        if (w <= 0) {
          return false;
        }
        // debug(st, w / x);
        auto it = --st.upper_bound(w / x);
        if (*it == 0) {
          return false;
        }
        // debug(*it, w / x);
        st.erase(it);
      }
      return true;
    };
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (check_neg(m)) {
        r = m;
      } else {
        l = m;
      }
    }

    // debug(r);
    cmax(hi, r);
  }

  {
    int l = -lnf, r = lnf;

    auto check_pos = [&](int t) {
      // debug(t);
      multiset<int> st(all(v1));
      st.emplace(0);
      st.emplace(lnf);
      // st.emplace(lnf);
      for (auto [x, y] : pos) {
        // y - x * k >= t
        // x * k <= y - t
        ll w = y - t;
        if (w <= 0) {
          return false;
        }
        auto it = --st.upper_bound(w / x);
        if (*it == 0) {
          return false;
        }
        st.erase(it);
      }
      return true; 
    };
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (check_pos(m)) {
        l = m;
      } else {
        r = m;
      }
    }
    cmin(lo, l);
  }
  cout << hi - lo << "\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}