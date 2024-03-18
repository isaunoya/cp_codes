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

int get(int a, int b, int w) {
  if (a == -1) {
    return b;
  }
  if (b == -1) {
    return a;
  }
  cout << "? " << a << " " << b << " " << w << endl;
  string s;
  cin >> s;
  if (s == "FIRST") {
    return a;
  } else {
    return b;
  }
}

const int N = 1e5;
int id[N * 4];
void update(int l, int r, int p, int x) {
  if (id[p] == -1) {
    id[p] = x;
    return;
  }
  if (get(id[p], x, l) == x) {
    swap(id[p], x);
  }
  if (l == r) {
    return;
  }
  int m = (l + r) / 2;
  if (get(id[p], x, m) == x)
    update(l, m, p * 2, id[p]), id[p] = x;
  else
    update(m + 1, r, p * 2 + 1, x);
}
int query(int l, int r, int p, int x) {
  if (l == r) {
    return id[p];
  }
  int m = (l + r) / 2;
  int y;
  if (x <= m)
    y = query(l, m, p * 2, x);
  else
    y = query(m + 1, r, p * 2 + 1, x);
  return get(id[p], y, x);
}

void solve() {
  memset(id, -1, sizeof id);
  int n;
  cin >> n;
  for (int b = 0; b < n; b++) {
    update(1, N, 1, b);
  }
  cout << "!" << endl;
  while (true) {
    string s;
    cin >> s;
    if (s == "QUESTION") {
      int x;
      cin >> x;
      int y = query(1, N, 1, x);
      cout << "! " << y << endl;
    } else {
      return;
    }
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