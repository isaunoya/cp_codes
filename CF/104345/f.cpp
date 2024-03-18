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
int n;
const int N = 1e5 + 5;
struct zkw{
  int t[N * 2];
  void upd(int x, int v){
    x += n;
    while (x) {
      t[x] += v;
      x /= 2;
    }
  }

  int query(int l, int r) { // [l, r)
    int ans = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        ans += t[l++];
      }
      if (r & 1) {
        ans += t[--r];
      }
    }
    return ans;
  }

  int sum() {
    return t[1];
  }
} t[10];

void solve() {
  string x, y;
  cin >> x >> y;
  n = sz(x);
  vi cnt(10), cnt2(10), cnt3(10);
  for (int i = 0; i < n; i++) {
    cnt[x[i] - '0'] += 1;
  }

  for (int i = 0; i < n; i++) {
    int c = y[i] - '0';
    t[c].upd(i, 1);
  }

  int q;
  cin >> q;
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int i, x;
      cin >> i >> x;
      i--;
      int c = y[i] - '0';
      t[c].upd(i, -1);
      y[i] = x + '0';
      t[x].upd(i, 1);
    } else {
      int i;
      cin >> i;
      for (int i = 0; i < 10; i++) {
        cnt2[i] = t[i].sum();
      }
      if (cnt == cnt2) {
        cout << y[i] << "\n";
      } else {

        auto check = [&](int x) {
          for (int i = 0; i < 10; i++) {
            cnt3[i] = cnt[i] - t[i].query(0, x);
            if (cnt3[i] < 0) {
              return false;
            }
          }
          int c = y[x] - '0';
          
        };

        int l = -1, r = n;
        while (r - l > 1) {
          int m = (l + r) / 2;
          if (check(m)) {
            l = m;
          } else {
            r = m;
          }
        }

      }
    }
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