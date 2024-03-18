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
template <class T> void read(vector<T> &v) {
  for (T &x : v)
    cin >> x;
}
template <class T, class S> void read(pair<T, S> &v) {
  cin >> v.first >> v.second;
}
template <class T, class... Ts> void read(T &a, Ts &...b) {
  read(a), read(b...);
}

const int B = 320;
void solve() {
  int n;
  cin >> n;
  vi a(n);
  read(a);
  string s;
  cin >> s;
  vi c(n);
  rep(i, n) {
    c[i] = s[i] - '0';
  }
  vector<int> L, R, tag;
  int cnt = 0;
  for (int i = 0; i < n; i += B) {
    L.pb(i);
    R.pb(min(i + B, n));
    tag.pb(0);
    cnt++;
  }
  vector<array<ll, 2>> sum(n);
  for (int i = 0; i < cnt; i++) {
    rep (j, L[i], R[i]) {
      sum[i][c[j]] ^= a[j];
    }
  }

  auto rebuild = [&](int x) {
    rep (i, L[x], R[x]) {
      c[i] ^= tag[x];
    }
    tag[x] = 0;
    sum[x][0] = sum[x][1] = 0;
    rep (i, L[x], R[x]) {
      sum[x][c[i]] ^= a[i];
    }
  };

  int q;
  read(q);
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int l, r;
      cin >> l >> r;
      --l;
      for (int i = 0; i < cnt; i++) {
        if (R[i] <= l) {
          continue;
        }
        if (L[i] >= r) {
          continue;
        }
        if (l >= L[i] && r <= R[i]) {
          rebuild(i);
          rep (j, l, r) {
            sum[i][c[j]] ^= a[j];
            c[j] ^= 1;
            sum[i][c[j]] ^= a[j];
          }
          continue;
        }
        if (l > L[i] && r >= R[i]) {
          rebuild(i);
          rep (j, l, R[i]) {
            sum[i][c[j]] ^= a[j];
            c[j] ^= 1;
            sum[i][c[j]] ^= a[j];
          }
        } else if (l <= L[i] && r < R[i]) {
          rebuild(i);
          rep (j, L[i], r) {
            sum[i][c[j]] ^= a[j];
            c[j] ^= 1;
            sum[i][c[j]] ^= a[j];
          }
        } else {
          tag[i] ^= 1;
          swap(sum[i][0], sum[i][1]);
        }
      }
    } else {
      int x;
      cin >> x;
      ll res = 0;
      for (int i = 0; i < cnt; i++) {
        res ^= sum[i][x];
      }
      cout << res << " ";
    }
  }
  cout << "\n";
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