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

int N, Q, L;
bool vis[2][1 << 22];
void update(int i, int v) {
  if (vis[i][v]) {
    return;
  }
  vis[i][v] = true;
  for (int j = 0; j < L; j++) {
    if (v >> j & 1) {
      update(i, v ^ 1 << j);
    }
  }
}

void solve() {
  cin >> N >> Q;
  L = 0;
  while (1 << L < N) {
    L++;
  }

  rep(1 << L) vis[0][i] = vis[1][i] = 0;

  int ans = 0;
  while (Q--) {
    int e;
    cin >> e;
    e = (e + ans) % N;
    {
      int cur = 0;
      for (int i = L - 1; i >= 0; i--) {
        if (e >> i & 1 && vis[0][cur | 1 << i]) {
          cur |= 1 << i;
        }
      }
      cmax(ans, cur);
    }
    {
      int cur = 0;
      for (int i = L - 1; i >= 0; i--) {
        if (!(e >> i & 1) && vis[1][cur | 1 << i]) {
          cur |= 1 << i;
        }
      }
      cmax(ans, cur);
    }
    update(0, (1 << L) - 1 - e);
    update(1, e);
    cout << ans << " \n"[Q == 0];
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