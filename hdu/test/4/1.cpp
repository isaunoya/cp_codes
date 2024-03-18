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

unordered_map<ll, ll> _mu;
const int maxn = 1e7;
ll mu[maxn + 10];

ll getmu(ll x) {
  if (x <= maxn)
    return mu[x];
  if (_mu[x])
    return _mu[x];
  ll l = 2, r = 0;
  ll ans = 1;
  for (; l <= x; l = r + 1) {
    r = x / (x / l);
    ans -= getmu(x / l) * (r - l + 1);
  }
  return _mu[x] = ans;
}

void sol() {
  mu[1] = 1;
  for (int i = 1; i <= maxn; i++)
    for (int j = i * 2; j <= maxn; j += i)
      mu[j] -= mu[i];
  for (int i = 2; i <= maxn; i++) {
    mu[i] += mu[i - 1];
  }
}

ll p;
ll power(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y % 2 == 1) {
      r = (__int128)r * x % p;
    }
    x = (__int128)x * x % p;
    y /= 2;
  }
  return r;
}

ll inv(ll x) {
  return power(x, p - 2);
}
void solve() {
  sol();
  ll n;
  cin >> n >> p;
  if (n == 1) {
    cout << 1 << "\n";
    return;
  }
  ll ans = 1;
  for (ll l = 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    ll coef = -(getmu(r) - getmu(l - 1));
    coef = (coef % p + p) % p;
    ll x = n / l;
    x %= p;
    ans += (__int128)coef * x % p * inv(n - x) % p;
    if (ans >= p) {
      ans -= p;
    }
    if (ans < 0) {
      ans += p;
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

/*

100000000000
998244353
*/