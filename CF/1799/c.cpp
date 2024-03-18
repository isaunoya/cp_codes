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
  string s;
  cin >> s;
  int cnt[26] = {0};
  tr(x, s) cnt[x - 'a']++;
  int n = sz(s);
  vector<int> ans(n);
  int l = 0, r = n - 1, p = -1;
  rep(i, 0, 26) {
    while (cnt[i] > 1)
      ans[l++] = ans[r--] = i, cnt[i] -= 2;
    if (cnt[i] == 1) {
      p = i;
      break;
    }
  }
  if (p != -1) {
    int c = 0;
    rep(i, 0, 26) if (cnt[i])++ c;
    if (c == 2) {
      rep(i, p + 1, 26) {
        while (cnt[i] > 1) {
          ans[l++] = ans[r--] = i;
          cnt[i] -= 2;
        }
        if (cnt[i] == 1)
          ans[l++] = i;
      }
      ans[r--] = p;
    } else {
      rep(i, p + 1, 26) {
        while (cnt[i]--)
          ans[l++] = i;
      }
      ans[r--] = p;
    }
  }
  for (auto x : ans) {
    cout << char(x + 'a');
  }
  cout << "\n";
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
