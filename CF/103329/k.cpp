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

const int maxn = 500005;
int b[maxn], pre[maxn], nxt[maxn];

int a[maxn];

void solve() {
  int n;
  cin >> n;
  bool ok = true;
  for (int i = 1; i <= n; i++)
    cin >> b[i];
  for (int i = 1; i <= n; i++) {
    if (b[i] < i) {
      ok = false;
      break;
    }
  }
  if (b[1] > n) {
    cout << -1 << "\n";
    return;
  }
  if (!ok) {
    cout << -1 << "\n";
    return;
  }
  ok = true;
  for (int i = 1; i <= n; i++) {
    if (b[i] == i) {

    } else {
      ok = false;
      break;
    }
  }

  if (ok) {
    rep(n) cout << 0 << " \n"[i + 1 == n];
    return;
  }

  ok = true;
  for (int i = 1; i <= n; i++) {
    ok &= b[i] > i;
  }

  if (!ok) {
    cout << -1 << "\n";
    return;
  }

  int mn = inf;
  for (int i = 1; i <= n; i++) {
    int len = (b[i] > n ? 2 * n : b[i]) - i + 1;
    cmin(mn, len);
  }

  for (int col = mn; col >= 2; col--) {
    fill(pre + 1, pre + n + 1, 0);
    fill(nxt + 1, nxt + n + 1, 0);
    int tot = 0;
    bool ok2 = true;
    for (int i = 1, j = col; i < n; i++) {
      if (!pre[i]) {
        tot++;
      }
      if (tot > col) {
        ok2 = false;
        break;
      }
      if (b[i] < b[i + 1]) {
        nxt[i] = b[i + 1];
        pre[b[i + 1]] = i;
      } else {
        while (j <= n && (pre[j] || j == b[1])) {
          j++;
        }
        nxt[i] = j;
        pre[j] = i;
      }
    }
    if (!ok2)
      continue;
    tot = 0;
    for (int i = 1; i <= n; i++) {
      if (pre[i]) {
        a[i] = a[pre[i]];
      } else {
        a[i] = ++tot;
      }
      cout << a[i] << " \n"[i == n];
    }
    return;
  }
  cout << -1 << "\n";
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