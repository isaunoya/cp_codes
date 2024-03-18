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
  int n;
  cin >> n;
  string s;
  cin >> s;
  auto p = manacher(s);

  vi l0(n);
  vi l1(n);

  vc<vi> v(n + 1);
  rep(i,n) {
    int len = p[i * 2 + 2];
    int lft = i - ((len + 1) / 2) + 1;
    v[lft].pb(i);
    v[i + 1].pb(~i);
  }
  multiset<int> ss;
  rep(i, n) {
    for (auto x : v[i]) {
      if (x >= 0) {
        ss.emplace(x);
      } else {
        ss.erase(ss.find(~x));
      }
    }
    l1[i] = 2*i-*ss.rbegin();
  }
  rep(i, n + 1) v[i].clear();
  rep(i, n) {
    int len = p[i * 2 + 1];
    int lft = i - len / 2;
    v[lft].pb(i);
    v[i].pb(~i);
  }
  ss.clear();
  rep(i, n) {
    for (auto x : v[i]) {
      if (x >= 0) {
        ss.emplace(x);
      } else {
        ss.erase(ss.find(~x));
      }
    }
    // debug(ss);
    if(sz(ss)) l0[i] = 2*i+2-*ss.rbegin();
    else l0[i]=i-1;
  }

  vi r1(n);
  vi r0(n);
  rep(i,n){
    
  }
  // debug(l1, l0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}