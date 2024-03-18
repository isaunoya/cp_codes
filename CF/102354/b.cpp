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

int n;
const int N = 100050;
int a[N], b[N];
int ans[N];
vector<int> divisor[N];
int mu[N];

vector<int> q[N];
int x[N], y[N], p[N], l[N], r[N], cnt[N];
int solve(int m) {
  for (int i = 1; i <= m; i++) {
    p[i] = i;
  }
  sort(p + 1, p + m + 1, [&](int a, int b) { return y[a] < y[b]; });
  for (int i = 1; i <= m; i++) {
    l[i] = 1, r[i] = m;
  }
  while (true) {
    bool ok = true;
    for (int i = 1; i <= m; i++) {
      q[i].clear();
      cnt[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
      if (l[i] < r[i]) {
        ok = false;
        int mid = (l[i] + r[i]) / 2;
        q[mid].emplace_back(i);
      }
    }
    if (ok) {
      break;
    }
    for (int t = 1; t <= m; t++) {
      for (auto d : divisor[p[t]]) {
        cnt[d]++;
      }
      for (auto i : q[t]) {
        int res = 0;
        for (auto d : divisor[i]) {
          res += cnt[d] * mu[d];
        }
        if (res) {
          r[i] = t;
        } else {
          l[i] = t + 1;
        }
      }
    }
  }
  int mx = 0;
  for (int i = 1; i <= m; i++) {
    cmax(mx, x[i] - y[p[l[i]]]);
  }
  return mx;
}

void solve() {
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      x[j / i] = a[j];
      y[j / i] = b[j];
    }
    cmax(ans[i], solve(n / i));
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  mu[1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i * 2; j <= n; j += i) {
      mu[j] -= mu[i];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      divisor[j].emplace_back(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  solve();
  for (int i = 1; i <= n; i++) {
    swap(a[i], b[i]);
  }
  solve();
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}