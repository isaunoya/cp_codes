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

void solve() {
  int N;
  cin >> N;
  int t = 0;
  while ((1 << t) < N) {
    t++;
  }
  int M = 1 << t;
  using u32 = unsigned;
  vector<u32> dat(M * 2, -1);
  for (int i = 0; i < N; i++) {
    u32 x;
    cin >> x;
    int j = i + M;
    dat[j] = x;
    while (j >>= 1) {
      dat[j] = dat[j * 2] & dat[j * 2 + 1];
    }
  }
  auto max_right = [&](int L, auto check) {
    L += M;
    u32 res = -1;
    do {
      while (L % 2 == 0) {
        L /= 2;
      }
      if (!check(res & dat[L])) {
        while (L < M) {
          L *= 2;
          if (check(res & dat[L])) {
            res &= dat[L++];
          }
        }
        return L - M;
      }
      res &= dat[L++];
    } while ((L & -L) != L);
    return N;
  };
  int Q;
  cin >> Q;
  while (Q--) {
    int L, K;
    cin >> L >> K;
    --L;
    int R = max_right(L, [&](auto e) -> bool { return e >= K; });
    if (R <= L) {
      R = -1;
    }
    cout << R << " \n"[Q == 0];
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