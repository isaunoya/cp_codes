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
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    cin >> x;
}
template <class T, class S> void read(pair<T, S> &v) {
  cin >> v.first >> v.second;
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}


void solve() {
  int n, m;
  cin >> n >> m;
  set<int> s[2]; // [x-y]
  for (int i = -m+1; i <= n-1; i++) {
    s[(i % 2 + 2) % 2].insert(i);
  }
  vc<array<int, 3>> seg[2];
  for (int i = 0; i < n + m - 1; i++) {
    int x = min(i, n - 1);
    int y = i - x;
    int L = x - y;
    y = min(i, m - 1);
    x = i - y;
    int R = x - y;
    swap(L, R);
    int p = i % 2;
    p = (p + 2) % 2;
    seg[p].pb(array<int, 3>{L, R, i});
  }
  vc<pii> ans;
  for (int p = 0; p < 2; p++) {
    int beg = -m + 1;
    if ((beg % 2 + 2) % 2 != p) {
      beg++;
    }
    auto v = seg[p];
    sort(all(v));
    debug(v);
    pqg<pii> t;
    int k = 0;
    for (int i = beg; i <= n - 1; i += 2) {
      while (!t.empty() && (t.top()).first < i) {
        t.pop();
      }
      while (k < sz(v) && v[k][0] == i) {
        t.emplace(v[k][1], v[k][2]);
        k += 1;
      }
      if (t.empty()) {
        continue;
      }
      debug(t.top());
      auto [jj, ii] = t.top();
      ans.emplace_back((ii + i) / 2, (ii - i) / 2);
      t.pop();
    }
  }
  
  cout << sz(ans) << "\n";
  for (auto [x, y] : ans) {
    cout << x + 1 << " " << y + 1 << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
//  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
