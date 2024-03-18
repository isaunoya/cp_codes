#include <bits/stdc++.h>
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
template <typename T> using vc = vector<T>;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

vector<int> manacher(const string &s) {
  vector<int> p(s.size() * 2 + 1);
  string t = "~";
  t += "-";
  for (int i = 0; i < (int)s.size(); i++) {
    t += s[i];
    t += "-";
  }
  int n = (int)t.size();
  int m = -1, r = -1;
  for (int i = 0; i < n; i++) {
    if (i <= r) {
      p[i] = min(p[m * 2 - i], r - i + 1);
    }
    while (i - p[i] >= 0 && i + p[i] < n && t[i + p[i]] == t[i - p[i]]) {
      ++p[i];
    }
    if (i + p[i] > r) {
      r = i + p[i] - 1;
      m = i;
    }
    --p[i];
  }
  string().swap(t);
  return p;
}

void solve() {
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  auto p = manacher(s);
  vi lst(26, INF);
  vi nx(n);
  for (int i = n - 1; i >= 0; i--) {
    nx[i] = lst[s[i] - 'a'] - i;
    lst[s[i] - 'a'] = i;
  }
  vi t1(n * 2), t2(n * 2);
  rep(i, n) { t1[i + n] = nx[i], t2[i + n] = nx[i]; }
  for (int i = n - 1; i >= 1; i--) {

    t1[i] = max(t1[i * 2], t1[i * 2 + 1]);

    t2[i] = min(t2[i * 2], t2[i * 2 + 1]);
  }
  auto query = [&](int l, int r) {
    int mn = INF, mx = -INF;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        cmax(mx, t1[l]);

        cmin(mn, t2[l]);
        l += 1;
      }
      if (r & 1) {
        r -= 1;
        cmax(mx, t1[r]);

        cmin(mn, t2[r]);
      }
    }
    return make_pair(mn, mx);
  };
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l;
    int pa = p[l + r + 1];
    if (r - l == 2) {
      if (s[l] == s[l + 1]) {
        cout << 0 << "\n";
      } else {
        cout << 2 << "\n";
      }
    } else {
      auto [mn, mx] = query(l, r - 1);
      if (mx == 1 && mn == 1) {
        cout << 0 << "\n";
      } else {
        auto [mn, mx] = query(l, r - 2);
        if (mx == 2 && mn == 2) {
          long long ans = 0;
          int len = r - l;
          int k = len;
          if (k % 2 == 1) {
            k--;
          }
          ans += 1ll * k * (k / 2 + 1) / 2;
          cout << ans << "\n";
        } else {
          int len = r - l;
          long long ans = 1ll * len * (len + 1) / 2 - 1;
          if (pa >= len) {
            ans -= len;
          }
          cout << ans << "\n";
        }
      }
    }
  }
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