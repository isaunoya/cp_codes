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

void solve() {
  int n, m;
  cin >> n >> m;
  vc<array<int, 4>> op(m);
  vi a11, a22;
  vi a12, a21;
  rep(i, m) {
    int l, x, r, y;
    cin >> l >> x >> r >> y;
    --l;
    --r;
    op[i] = array<int, 4>{l, x, r, y};
    if (x == 1 && y == 1)
      a11.pb(i);
    if (x == 2 && y == 2)
      a22.pb(i);
    if (x == 1 && y == 2)
      a12.pb(i);
    if (x == 2 && y == 1)
      a21.pb(i);
  }

  sort(all(a12), [&](int x, int y) { return op[x][2] > op[y][2]; });
  sort(all(a21), [&](int x, int y) { return op[x][0] < op[y][0]; });
  auto get = [&](vi p) {
    vi a(n);
    for (auto i : p) {
      auto [l, x, r, y] = op[i];
      a[l] = x;
      a[r] = y;
    }
    return accumulate(all(a), 0);
  };
  int ans1;
  vi p;
  p.clear();
  p.insert(p.end(), all(a11));
  p.insert(p.end(), all(a21));
  p.insert(p.end(), all(a12));
  p.insert(p.end(), all(a22));
  ans1 = get(p);
  int ans2;
  p.clear();
  p.insert(p.end(), all(a11));
  p.insert(p.end(), all(a12));
  p.insert(p.end(), all(a21));
  p.insert(p.end(), all(a22));
  ans2 = get(p);

  if (ans1 > ans2) {
    p.clear();
    p.insert(p.end(), all(a11));
    p.insert(p.end(), all(a21));
    p.insert(p.end(), all(a12));
    p.insert(p.end(), all(a22));
    cout << ans1 << "\n";
    for (int i : p) {
      cout << i + 1 << " ";
    }
    cout << "\n";
  } else {
    p.clear();
    p.insert(p.end(), all(a11));
    p.insert(p.end(), all(a12));
    p.insert(p.end(), all(a21));
    p.insert(p.end(), all(a22));
    cout << ans2 << "\n";
    for (int i : p) {
      cout << i + 1 << " ";
    }
    cout << "\n";
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