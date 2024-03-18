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
  int n, m;
  cin >> n >> m;
  vi a(n);
  rep(i, n) {
    char c;
    cin >> c;
    int x = c - 'a';
    a[i] = x;
  }
  set<pii> ban;
  rep(i, n) {
    if (i + 1 < n && a[i] == a[i + 1]) {
      ban.emplace(i, i + 1);
    }
    if (i + 2 < n && a[i] == a[i + 2]) {
      ban.emplace(i, i + 2);
    }
  }
  vi t(n * 2, 0);
  auto pu = [&](int x) { t[x] = t[x * 2] + t[x * 2 + 1]; };
  auto add = [&](int x, int v) {
    x += n;
    t[x] += v;
    while (x >>= 1) {
      pu(x);
    }
  };
  auto query = [&](int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        ans += t[l++];
      }
      if (r & 1) {
        ans += t[--r];
      }
    }
    return ans;
  };

  while (m--) {
    // debug(ban);
    int o;
    cin >> o;
    if (o == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      --l;
      --r;
      for (auto y : {l - 2, l - 1, l, r - 2, r - 1, r}) {
        if (y < 0)
          continue;
        int v = a[y] + query(0, y + 1);
        v %= 26;
        if (y + 1 >= n)
          continue;
        int v1 = a[y + 1] + query(0, y + 2);
        v1 %= 26;
        if (v == v1) {
          ban.erase(pii(y, y + 1));
        }
        if (y + 2 >= n)
          continue;
        int v2 = a[y + 2] + query(0, y + 3);
        v2 %= 26;
        if (v == v2) {
          ban.erase(pii(y, y + 2));
        }
      }
      x %= 26;
      add(l, x);
      if (r + 1 < n) {
        add(r + 1, 26 - x);
      }
      for (auto y : {l - 2, l - 1, l, r - 2, r - 1, r}) {
        if (y < 0)
          continue;
        int v = a[y] + query(0, y + 1);
        v %= 26;
        if (y + 1 >= n)
          continue;
        int v1 = a[y + 1] + query(0, y + 2);
        v1 %= 26;
        if (v == v1) {
          ban.emplace(pii(y, y + 1));
        }
        if (y + 2 >= n)
          continue;
        int v2 = a[y + 2] + query(0, y + 3);
        v2 %= 26;
        if (v == v2) {
          ban.emplace(pii(y, y + 2));
        }
      }
    } else {
      int l, r;
      cin >> l >> r;
      --l;
      --r;
      auto it = ban.lower_bound(pii(l, l));
      bool ans = false;
      if (it != ban.end() && (*it).se <= r) {
        ans = true;
      }
      if (ans) {
        cout << "No\n";
      } else {
        cout << "Yes\n";
      }
    }
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