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

int read() {
  string s;
  cin >> s;
  assert(sz(s) == 2);

  if ('0' <= s[0] && s[0] <= '9')
    return s[0] - '0';
  if (s[0] == 'T')
    return 10;
  if (s[0] == 'J')
    return 11;
  if (s[0] == 'Q')
    return 12;
  if (s[0] == 'K')
    return 13;
  if (s[0] == 'A')
    return 14;

  assert(0);
  return -1;
}

bool solve() {
  int n, m;
  cin >> n >> m;
  vi a(n), b(m);
  rep(i, n) a[i] = read();
  rep(i, m) b[i] = read();
  int p = read();
  int ca = 0;
  rep(i, n) if (a[i] < p) ca++;

  int cb = 0;
  rep(i, m) if (b[i] < p) cb++;

  int la = 0;
  rep(i, n) if (a[i] < p) cmax(la, a[i]);
  int lb = 0;
  rep(i, m) if (b[i] < p) cmax(lb, b[i]);

  int ma = *max_element(all(a));
  int mb = *max_element(all(b));

  if (n == 1) {
    return false;
  }

  // ca > 0
  if (n == 2) {
    if (ca == 0)
      return false;
    if (m == 1) {
      return b[0] <= la;
    }
    // m >= 2
    if (mb < p) {
      return true;
    }
    // mb >= p
    if (cb > 1) {
      return true;
    } else {
      return false;
    }
  }

  // n >= 3
  if (cb == 0) {
    // b can win every case.
    return false;
  }

  if (cb == 1) {
    if (m == 1) {
      return la >= lb;
    }

    // m >= 2, cb = 1

    if (n == 3) {
      // 0 means < p
      // 1 means >= p
      // 0 0 1, lose
      // 0, and b >= p
      // 1, and b do nothing
      // 0, and a lose
      // 0 1 1, lose
      // 1 1 1, lose
      return false;
    }
    // n > 3
    if (ma > mb && ca > 1 && la >= lb) {
      return true;
    } else {
      return false;
    }
  }

  // cb > 1, also means m >= 2
  if (ca == 0) {
    return false;
  } else {
    return true;
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    if (solve())
      cout << "Pang\n";
    else
      cout << "Shou\n";
  }
  return 0;
}