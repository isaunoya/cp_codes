#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
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
#define fi first
#define se second
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

template <class... T> void read() {}
template <class T> void read(T &x) { cin >> x; }
template <class T, class S> void read(pair<T, S> &v) {
  read(v.first, v.second);
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}


using i28 = __int128;

void solve() {
  long long n, k;
  read(n, k);
  if (n < k) {
    cout << n << "\n";
    return;
  }

  vector<pair<ll, ll>> seg;
  for (ll l = 1, r; l <= n; l = r + 1) {
    if (l > (n + 1) / k) {
      r = n;
    } else {
      r = l * k - 1;
    }
    seg.pb(l, r);
  }

  auto check = [&](ll x) -> ll{
    int cur = 0;
    while (x > seg[cur].se) {
      cur++;
    }
    ll ans = -x + 1;
    ll mul = 1;
    for (int i = cur - 1; i >= 0; i--) {
      mul = mul * k;
      ans += x / mul - seg[i].fi + 1;
    }
    mul = 1;
    for (int i = cur; i < seg.size(); i++) {
      ans += min((i28)x * mul - 1, (i28)n) - seg[i].fi + 1;
      mul = mul * k;
    }
    return ans;
  };

  ll ans = 0;
  for (auto [l, r] : seg) {
    ll ans1 = r + 1;
    ll ans2 = r + 1;
    {
      ll L = l - 1;
      ll R = r + 1;
      while (R - L > 1) {
        ll m = (L + R) / 2;
        if (check(m) >= 0) {
          R = m;
        } else {
          L = m;
        }
      }
      ans1 = R;
    }

    {
      ll L = l - 1;
      ll R = r + 1;
      while (R - L > 1) {
        ll m = (L + R) / 2;
        if (check(m) > 0) {
          R = m;
        } else {
          L = m;
        }
      }
      ans2 = R;
    }

    ans += ans2 - ans1;
  }

  cout << ans << "\n";
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