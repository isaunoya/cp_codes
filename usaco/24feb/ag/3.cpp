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
  int N, M, K;
  cin >> N >> M >> K;
  vc<array<int, 2>> t(M);
  rep(i, M) {
    vi mn(2, inf), mx(2);
    rep(j, K) {
      int x;
      cin >> x;
      cmin(mn[x % 2], x);
      cmax(mx[x % 2], x);
    }
    if (!mx[0]) {
      t[i][1] = mn[1];
      t[i][0] = -mx[1];
    } else if (!mx[1]) {
      t[i][0] = mn[0];
      t[i][1] = -mx[0];
    } else {
      t[i][0] = -mx[1];
      t[i][1] = -mx[0];
    }
  }
  int cur = N;

  vi T(M);
  rep(i, M) T[i] = max(t[i][0], t[i][1]);
  vi ST(M + 1);
  rep(i, M) ST[i + 1] = ST[i] + T[i];
  multiset<int> st(all(ST));

  if (N + *st.begin() <= 0) {
    cout << -1 << "\n";
    return;
  }

  rep(i, M) {
    st.erase(st.find(ST[i]));
    int p = cur + t[i][0];
    bool ok = true;
    if (p + *st.begin() - ST[i + 1] <= 0) {
      ok = false;
    }
    if (ok) {
      cout << "Even";
      cur += t[i][0];
    } else {
      cout << "Odd";
      cur += t[i][1];
    }
    cout << " \n"[i + 1 == M];
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