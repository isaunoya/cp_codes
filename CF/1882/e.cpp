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
  int N, M;
  cin >> N >> M;
  vi p(N), q(M);
  for (int i = 0; i < N; i++) {
    cin >> p[i];
    --p[i];
  }
  auto P = p;
  for (int i = 0; i < M; i++) {
    cin >> q[i];
    --q[i];
  }
  auto Q = q;
  // i+1....n (i) 1...(j)...i-1
  // j+1...i-1..j i+1 ... n i 1...j-1
  // 1...(j-1) (i) i-k+1 ... (j) i+1 ... n
  vi pp, qq;
  for (int i = 0; i < N; i++) {
    if (p[i] == i) {
      continue;
    }
    int pos = -1;
    for (int j = i; j < N; j++) {
      if (p[j] == i) {
        pos = j;
        break;
      }
    }
    // try to swap(i, pos)
    // i < pos
    pp.pb(pos);
    pp.pb(N - (pos - i));
    pp.pb(N - i - 1);
    swap(p[i], p[pos]);
  }

  // for (int x : pp) {
  //   vi np;
  //   for (int i = x + 1; i < N; i++) {
  //     np.pb(P[i]);
  //   }
  //   np.pb(P[x]);
  //   for (int i = 0; i < x; i++) {
  //     np.pb(P[i]);
  //   }
  //   P = np;
  // }
  // debug(P);

  for (int i = 0; i < M; i++) {
    if (q[i] == i) {
      continue;
    }
    int pos = -1;
    for (int j = i; j < M; j++) {
      if (q[j] == i) {
        pos = j;
        break;
      }
    }
    // try to swap(i, pos)
    // i < pos
    qq.pb(pos);
    qq.pb(M - (pos - i));
    qq.pb(M - i - 1);
    swap(q[i], q[pos]);
  }

  // for (int x : qq) {
  //   vi nq;
  //   for (int i = x + 1; i < M; i++) {
  //     nq.pb(Q[i]);
  //   }
  //   nq.pb(Q[x]);
  //   for (int i = 0; i < x; i++) {
  //     nq.pb(Q[i]);
  //   }
  //   Q = nq;
  // }
  // debug(Q);

  if (pp.size() % 2 == qq.size() % 2) {
    cout << max(pp.size(), qq.size()) << "\n";
    for (int i = 0; i < max(pp.size(), qq.size()); i++) {
      int x = (i % 2 == 1) ? 0 : (N - 1);
      int y = (i % 2 == 1) ? 0 : (M - 1);
      if (pp.size() > i) {
        x = pp[i];
      }
      if (qq.size() > i) {
        y = qq[i];
      }
      cout << x + 1 << " " << y + 1 << "\n";
    }
  } else {
    if (N % 2 == 1) {
      for (int i = 0; i < N; i++) {
        pp.pb(0);
      }
      cout << max(pp.size(), qq.size()) << "\n";
      for (int i = 0; i < max(pp.size(), qq.size()); i++) {
        int x = (i % 2 == 1) ? 0 : (N - 1);
        int y = (i % 2 == 1) ? 0 : (M - 1);
        if (pp.size() > i) {
          x = pp[i];
        }
        if (qq.size() > i) {
          y = qq[i];
        }
        cout << x + 1 << " " << y + 1 << "\n";
      }
      return;
    }
    if (M % 2 == 1) {
      for (int i = 0; i < M; i++) {
        qq.pb(0);
      }
      cout << max(pp.size(), qq.size()) << "\n";
      for (int i = 0; i < max(pp.size(), qq.size()); i++) {
        int x = (i % 2 == 1) ? 0 : (N - 1);
        int y = (i % 2 == 1) ? 0 : (M - 1);
        if (pp.size() > i) {
          x = pp[i];
        }
        if (qq.size() > i) {
          y = qq[i];
        }
        cout << x + 1 << " " << y + 1 << "\n";
      }
      return;
    }
    cout << -1 << "\n";
    return;
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