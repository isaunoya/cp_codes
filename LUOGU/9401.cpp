#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
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

template <class... T> void read() {}
template <class T> void read(T &x) { cin >> x; }
template <class T, class S> void read(pair<T, S> &v) {
  read(v.first, v.second);
}
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    read(x);
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

const int N = 5e5 + 5;
int n;
long long a[N];
long long st[20][N];
void solve() {
  cin >> n;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    int x;
    ll y;
    cin >> x >> y;
    a[x] = gcd(a[x], y);
    ans = gcd(ans, y);
  }

  for (int i = 0; i < N; i++) {
    st[0][i] = a[i];
  }

  for (int j = 1; j < 20; j++) {
    for (int i = 0; i + (1 << j) - 1 < N; i++) {
      st[j][i] = gcd(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
    }
  }

  auto query = [&](int l, int r) { // [l, r)
    int lg = __lg(r - l);
    return gcd(st[lg][l], st[lg][r - (1 << lg)]);
  };

  for (int i = 500000; i > ans; i--) {
    bool ok = true;
    for (int j = 0; i * j < 500000; j += 1) {
      int l = j * i + 1;
      int r = min((j + 1) * i, 500001);
      if (l >= r) {
        break;
      }
      if (query(l, r) % i) {
        ok = false;
        break;
      }
    }

    if (ok) {
      cout << i << "\n";
      return;
    }
  }

  cout << ans << "\n";
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