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
  
}

int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  string t;
  cin >> t;
  vi ans;
  rep(i, n) {
    string s;
    cin >> s;
    if (s.size() == t.size()) {
      if (s == t) {
        ans.pb(i);
        continue;
      } else {
        int cnt = 0;
        rep(j, s.size()) if (s[j] != t[j]) {
          cnt += 1;
        }
        if (cnt == 1) {
          ans.pb(i);
          continue;
        }
      }
    } else if (s.size() == t.size() + 1){
      int k = 0;
      rep(j, s.size()) if (k < t.size() && s[j] == t[k]) {
        k += 1;
      }
      if (k == t.size()) {
        ans.pb(i);
        continue;
      }
    } else if (s.size() + 1 == t.size()) {
      int k = t.size() - 1;
      rep(j, s.size()) if (s[j] != t[j]) {
        k = j;
        break;
      }
      s.insert(s.begin() + k, t[k]);
      if (s == t) {
        ans.pb(i);
      }
    }
  }
  cout << (int) ans.size() << "\n";
  for (int x : ans) {
    cout << x + 1 << " ";
  }
  return 0;
}