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

vector<array<int, 6>> op;
int get(ll X, ll Y) {
  int res = '.';
  for (auto t : op) {
    int o = t[0];
    if (o == 1) {
      ll x = t[1];
      ll y = t[2];
      ll r = t[3];
      if ((X - x) * (X - x) + (Y - y) * (Y - y) <= r * r) {
        res = t[4];
      }
    } else {
      ll x1 = t[1];
      ll y1 = t[2];
      ll x2 = t[3];
      ll y2 = t[4];
      if (x1 <= X && X <= x2 && y1 <= Y && Y <= y2) {
        res = t[5];
      }
    }
  }
  return res;
}

void solve() {
  int n;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;

    int o;
    if (s == "Circle") {
      o = 1;
    } else if (s == "Rectangle") {
      o = 2;
    } else {
      o = 3;
    }

    if (o == 1) {
      int x, y, r;
      char c;
      cin >> x >> y >> r;
      cin >> c;
      op.pb(array<int, 6>{o, x, y, r, c, 0});
    } else if (o == 2) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      char c;
      cin >> c;
      op.pb(array<int, 6>{o, x1, y1, x2, y2, c});
    } else {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      for (int i = y2; i >= y1; i--) {
        for (int j = x1; j <= x2; j++) {
          cout << char(get(j, i));
        }
        cout << "\n";
      }
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