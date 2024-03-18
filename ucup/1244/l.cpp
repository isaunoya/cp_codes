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

const int N = 1e6 + 5;
int isprime[N], prime[N], c = 0;
int f[N];
const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
void solve() {
  int n, k;
  cin >> n >> k;
  if ((n + k) % 2 == 1) {
    cout << "-1\n";
    return;
  }
  // vector<int> a;
  int cnt = 0;
  for (int i = 0; i < c; i++) {
    if (prime[i] > n) {
      break;
    } else if (prime[i] > n / 2) {
      cnt += 1;
    } else {
      // a.pb(prime[i]);
    }
  }

  rep(s, 1 << 9) {
    vi b;
    rep(i, 9) if (s >> i & 1) b.pb(p[i]);
    for (int i = 1; i <= n; i++)
      f[i] = 1;
    for (int i = 2; i <= n; i++) {
      for (int x : b) {
        if (i % x == 0) {
          f[i] = -f[i / x];
          break;
        }
      }
    }
    int w = 0;
    for (int i = 1; i <= n; i++)
      w += f[i];
    if (w - cnt * 2 <= k && k <= w) {
      int t = (w - k) / 2;
      for (int i = n / 2 + 1; i <= n; i++) {
        if (t == 0) {
          break;
        }
        if (isprime[i]) {
          f[i] = -1;
          t -= 1;
        }
      }
      for (int i = 1; i <= n; i++) {
        cout << f[i] << " \n"[i == n];
      }
      return;
    }
  }

  cout << "-1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  rep(i, 2, N) isprime[i] = 1;
  rep(i, 2, N) {
    if (isprime[i]) {
      prime[c++] = i;
      for (int j = i * 2; j < N; j += i) {
        isprime[j] = 0;
      }
    }
  }
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}