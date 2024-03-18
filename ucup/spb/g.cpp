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

void solve() {
  int n, m;
  cin >> n >> m;
  vc<pii> e(m);
  vc<unordered_map<int, int>> mp(n);
  vi deg(n);
  for (int i = 0; i < m; i++) {
    auto &[x, y] = e[i];
    cin >> x >> y;
    --x, --y;
    mp[x][y] = mp[y][x] = i + 1;
    ++deg[x];
    ++deg[y];
  }
  int q;
  cin >> q;
  vector<array<int, 2>> op(q);
  for (int i = 0; i < q; i++) {
    string o;
    cin >> o;
    if (o == "+") {
      int x;
      cin >> x;
      --x;
      op[i] = {1, x};
    } else if (o == "-") {
      int x;
      cin >> x;
      --x;
      op[i] = {2, x};
    } else {
      op[i] = {3, -1};
    }
  }
  vi ban(n), ban_edge(m), tag(n);
  const int B = 400;
  for (int L = 0; L < q; L += B) {
    int R = min(L + B, q);
    vi valid, cg;
    rep (i, n) tag[i] = 0;
    rep (i, L, R) if (op[i][0] < 3) {
      tag[op[i][1]] = 1;
      cg.pb(op[i][1]);
    }
    rep (i, m) {
      if (ban_edge[i]) {
        continue;
      }
      auto [x, y] = e[i];
      if ((ban[x] + ban[y] == 1) || (tag[x] + tag[y] > 0)) {
        valid.pb(i + 1);
      }
    }
    vi big;
    rep(i, n) if (deg[i] > B) big.pb(i);
    int p = 0;
    for (int i = L; i < R; i++) {
      if (op[i][0] < 3) {
        int x = op[i][1];
        if (op[i][0] == 1) {
          ban[x] = 1;
        } else {
          ban[x] = 0;
        }
        if (deg[x] > B) {
          for (auto y : cg) {
            if (mp[x].count(y)) {
              valid.pb(mp[x][y]);
            }
          }
          for (auto y : big) {
            if (mp[x].count(y)) {
              valid.pb(mp[x][y]);
            }
          }
        }
        int cnt = 0;
        for (auto [y, i] : mp[x]) {
          valid.pb(i);
          if (++cnt == B) {
            break;
          }
        }
      } else {
        bool ok = false;
        while (p < sz(valid)) {
          int id = valid[p++];
          --id;
          if (ban_edge[id]) {
            continue;
          }
          auto [x, y] = e[id];
          if (ban[x] + ban[y] == 1) {
            ban_edge[id] = 1;
            mp[x].erase(y);
            mp[y].erase(x);
            ok = true;
            cout << id + 1 << "\n";
            break;
          }
        }
        if (!ok) {
          cout << 0 << "\n";
          valid.clear();
          valid.shrink_to_fit();
          p = 0;
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}