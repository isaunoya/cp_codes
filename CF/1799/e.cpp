#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
using namespace std;
#define tr(x, v) for (auto &x : v)
#define rp(i, v) for (int i = 0; i < sz(v); i++)
#define rep(i, x, y) for (int i = x; i < y; i++)
#define pr(i, v) for (int i = sz(v) - 1; i >= 0; i--)
#define per(i, x, y) for (int i = x; i > y; i--)
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  if (x > y)
    x = y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  if (x < y)
    x = y;
}
using ll = long long;
using E = vector<vector<int>>;
using EW = vector<vector<array<int, 2>>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define ed(x) end(x)
#define all(x) bg(x), ed(x)
#define lb lower_bound
#define ub upper_bound
#define unique(x) (x).erase(unique(all(x)), x.end())
void out(bool t) { cout << (t ? "YES" : "NO") << "\n"; }
template <class T> T max(const vector<T> &v) { return *max_element(all(v)); }
template <class T> T min(const vector<T> &v) { return *min_element(all(v)); }
template <class T> istream &operator>>(istream &is, vector<T> &v) {
  tr(x, v) { is >> x; }
  return is;
}
template <class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  if (v.empty()) {
    os << "\n";
  } else {
    rp(i, v) os << v[i] << " \n"[i + 1 == (int)v.size()];
  }
  return os;
}

void run_case() {
  //  static int c = 0; cout << "case" << ++c << "\n";
  int n, m;
  cin >> n >> m;
  vector<vector<char>> a(n, vector<char>(m));
  rep(i, 0, n) rep(j, 0, m) cin >> a[i][j];
  vector<int> fir(n, m + 1), lst(n, -1);
  multiset<int> all;
  rep(i, 0, n) rep(j, 0, m) if (a[i][j] == '#') {
    if (fir[i] == m + 1)
      fir[i] = j;
    lst[i] = j;
    all.insert(j);
  }
  per(i, n - 1, -1) {
    if (fir[i] == m + 1)
      continue;
    //    cout << fir[i] << " " << lst[i] << "\n";
    rep(j, fir[i], lst[i] + 1) {
      if (a[i][j] == '.')
        a[i][j] = '#';
      else {
        auto ptr = all.find(j);
        if (ptr != all.end()) {
          all.erase(ptr);
        }
      }
    }
    if (i > 0) {
      if (all.empty())
        continue;
      int mn = *all.begin(), mx = *all.rbegin();
      if (mn < fir[i])
        cmin(fir[i - 1], fir[i]); // keep decrease
      else
        fir[i - 1] = min(lst[i], mn); // keep increase
      if (mx > lst[i])
        cmax(lst[i - 1], lst[i]);
      else
        lst[i - 1] = max(fir[i], mx);
    }
  }
  rep(i, 0, n) {
    rep(j, 0, m) cout << a[i][j];
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    run_case();
  }

  return 0;
}
