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

const int P = 998244353;
void solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  vector<int> B(N + 1);
  for (int i = 0; i < N; i++) {
    B[i + 1] = B[i] ^ A[i];
  }
  vector<long long> cnt1(30);
  vector<long long> cnt2(30);
  vector<long long> cnt3(30);
  vector<long long> cnt4(30);
  long long ans = 0;
  long long res = 0;
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j < i; j++) {
      res += 1ll * (B[i] ^ B[j]) * (i - j) % P;
    }
    for (int j = 0; j < 30; j++) {
      if (B[i] >> j & 1) {
        long long w = cnt2[j];
        long long v = cnt4[j];
        ans += 1ll * (w * i - v) % P * (1LL << j) % P;
        if (ans >= P) {
          ans -= P;
        }
      } else {
        long long w = cnt1[j];
        long long v = cnt3[j];
        ans += 1ll * (w * i - v) % P * (1LL << j) % P;
        if (ans >= P) {
          ans -= P;
        }
      }
    }
    debug(ans, res);
    for (int j = 0; j < 30; j++) {
      if (B[i] >> j & 1) {
        cnt1[j]++;
        cnt3[j] += i;
      } else {
        cnt2[j]++;
        cnt4[j] += i;
      }
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