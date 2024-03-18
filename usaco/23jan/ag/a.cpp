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

const int N = 1505;
string a[N];
int f[N][N];
ll s[N][N];

void solve() {
  int n;
  cin >> n;
  rep(i, n) {
    cin >> a[i];
    cin >> f[i][n];
  }

  rep(i, n) { cin >> f[n][i]; }

  int q;
  cin >> q;
  rep(t, q + 1) {
    int x, y;
    if (t) {
      cin >> x >> y;
      --x;
      --y;
      if (a[x][y] == 'R') {
        a[x][y] = 'D';
      } else {
        a[x][y] = 'R';
      }
    } else {
      x = n - 1, y = n - 1;
    }

    for (int i = x; i >= 0; i--) {
      for (int j = y; j >= 0; j--) {
        if (a[i][j] == 'R') {
          f[i][j] = f[i][j + 1];
        } else {
          f[i][j] = f[i + 1][j];
        }
        s[i][j] = f[i][j] + s[i][j + 1] + s[i + 1][j] - s[i + 1][j + 1];
      }
    }

    cout << s[0][0] << "\n";
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