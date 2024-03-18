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
  int n;
  cin >> n;
  if (n == 1) {
    cout << "1\n";
  } else if (n == 3) {
    cout << "169\n196\n961\n";
  } else if (n == 5) {
    cout << "16384\n31684\n36481\n38416\n43681\n";
  } else if (n == 7) {
    cout << "1638400\n3168400\n3648100\n3806401\n3841600\n4036081\n4368100\n";
  } else {
    vc<string> ans;
    ans.pb("100160064");
    ans.pb("101606400");
    ans.pb("116640000");
    ans.pb("166410000");
    ans.pb("400160016");
    ans.pb("401601600");
    ans.pb("416160000");
    ans.pb("610040601");
    ans.pb("661004100");
    for (auto &s : ans) s += string(n - s.size(), '0');
    for (int i = 0; i <= n - 11; i += 2) {
      string A = "1";
      int j = (i + 6) / 2;
      rep(k, j) {
        A += "0";
      }
      A += "16";
      rep(k, j) {
        A += "0";
      }
      A += "64";
      A += string(n - A.size(), '0');
      ans.pb(A);
    }
    for (int i = 0; i <= n - 11; i += 2) {
      string A = "4";
      int j = (i + 6) / 2;
      rep(k, j) {
        A += "0";
      }
      A += "16";
      rep(k, j) {
        A += "0";
      }
      A += "16";
      A += string(n - A.size(), '0');
      ans.pb(A);
    }
    for (auto A : ans) {
      cout << A << "\n";
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