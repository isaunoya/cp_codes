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
  int N, D;
  cin >> N >> D;
  vc<vc<double>> v(N, vc<double>(D));
  rep(i, N) {
    rep(j, D) {
      string s;
      cin >> s;
      double d = stod(s);
      v[i][j] = d;
    }
  }

  auto distance = [&](const vc<double> &v1, const vc<double> &v2) {
    double res = 0;
    rep(i, D) { res += (v1[i] - v2[i]) * (v1[i] - v2[i]); }
    return res;
  };
  cout << "ok" << endl;
  vi p(N);
  int k;
  cin >> k;
  auto query = [&](const vc<double> &q) {
    vc<double> s(N);
    rep(i, N) {
      s[i] = distance(q, v[i]);
      p[i] = i;
    }
    sort(all(p), [&](int x, int y) { return s[x] < s[y]; });
    vi ans;
    rep(i, k) ans.pb(p[i]);
    return ans;
  };

  vc<double> que(D);
  while (true) {
    string s;
    cin >> s;
    if (s == "end") {
      break;
    }
    que[0] = stod(s);
    rep(i, 1, D) {
      cin >> s;
      que[i] = stod(s);
    }
    auto v = query(que);
    for (int w : v) {
      cout << w << " ";
    }
    cout << endl;
  }
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