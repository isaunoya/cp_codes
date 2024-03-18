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
#define all(x) begin(x), end(x)
#define fi first
#define se second

double dis(const pii &x, const pii &y) {
  return sqrt((x.fi - y.fi) * (x.fi - y.fi) + (x.se - y.se) * (x.se - y.se));
}
double var(const vc<pii> &a) {
  double sx = 0, sy = 0;
  rep(i, a.size()) sx += a[i].fi, sy += a[i].se;
  sx /= a.size(), sy /= a.size();
  double vx = 0, vy = 0;
  rep(i, a.size()) vx += (a[i].fi - sx) * (a[i].fi - sx),
      vy += (a[i].se - sy) * (a[i].se - sy);
  return 1. * (vx + vy);
}

const int K = 100000;
const int W = 10;
pair<double, int> p[K];
pii t[20][20];
int g[20][W];

struct answer {
  double time;
  int lstx, lsty;
  int lstid, s;
} w[W], tmp[W * W * 10 * 10 * 2], bu[20][W];
int c = 0;

void solve() {
  rep(i, 20) rep(j, 20) cin >> t[i][j].fi >> t[i][j].se;
  rep(tt, 7) {
    // value, state
    rep(ss, K) {
      int s = rng() & 1048575;
      vc<pii> x, y;
      rep(j, 20) if (s >> j & 1) x.pb(t[tt][j]);
      else y.pb(t[tt][j]);
      p[ss].fi = var(x) + var(y);
      p[ss].se = s;
    }
    sort(p, p + K);
    rep(ss, W) { g[tt][ss] = p[ss].se; }
    //    rep(ss,W){
    //      debug(__builtin_popcount(g[tt][ss]));
    //    }
  }

  auto sol = [&](const pii &p, const vc<pii> &w) {
    int n = w.size();
    vc<vc<double>> d(1 << n, vc<double>(n, inf));
    rep(i, n) d[1 << i][i] = dis(p, w[i]);
    rep(s, 1, 1 << n) {
      rep(i, n) {
        if (s >> i & 1) {
          rep(j, n) {
            if (~s >> j & 1) {
              cmin(d[s | 1 << j][j], d[s][i] + dis(w[i], w[j]));
            }
          }
        }
      }
    }
    return d.back();
  };
  w[c++] = (answer){0, -1, -1, 0};
  rep(tt, 8) {
    memcpy(bu[tt], w, sizeof w);
    //    debug(c);
    int cc = 0;
    rep(k, c) {
      double tm = w[k].time;
      int xxx = w[k].lstx;
      int yyy = w[k].lsty;
      pii xx, yy;
      if (tt > 0) {
        xx = t[tt - 1][xxx];
        yy = t[tt - 1][yyy];
      } else {
        xx = pii(7, 7);
        yy = pii(8, 8);
      }
      rep(ss, W) {
        int s = g[tt][ss];
        vc<pii> x, y;
        vi xi, yi;
        rep(j, 20) if (s >> j & 1) x.pb(t[tt][j]), xi.pb(j);
        else y.pb(t[tt][j]), yi.pb(j);
        auto d1 = sol(xx, x);
        auto d2 = sol(yy, y);
        rep(i, xi.size()) {
          rep(j, yi.size()) {
            int ii = xi[i];
            int jj = yi[j];
            tmp[cc++] = (answer){tm + max(d1[i], d2[j]), ii, jj, k, s};
          }
        }
        s = 1048575 - s;
        swap(x, y);
        swap(xi, yi);
        d1 = sol(xx, x);
        d2 = sol(yy, y);
        rep(i, xi.size()) {
          rep(j, yi.size()) {
            int ii = xi[i];
            int jj = yi[j];
            tmp[cc++] = (answer){tm + max(d1[i], d2[j]), ii, jj, k, s};
          }
        }
      }
    }
    //    debug(cc);
    sort(tmp, tmp + cc, [&](answer x, answer y) { return x.time < y.time; });
    memcpy(w, tmp, sizeof w);
    c = min(cc, W);
  }
  memcpy(bu[8], w, sizeof w);
  debug(w[0].time);
  int id = 0;

  auto sol2 = [&](const pii &p, const vc<pii> &w, const pii &p2) {
    int n = w.size();
    vc<vc<double>> d(1 << n, vc<double>(n, inf));
    vc<vi> pre(1 << n, vi(n, -1));
    rep(i, n) d[1 << i][i] = dis(p, w[i]);
    rep(s, 1, 1 << n) {
      rep(i, n) {
        if (s >> i & 1) {
          rep(j, n) {
            if (~s >> j & 1) {
              if (d[s | 1 << j][j] > d[s][i] + dis(w[i], w[j])) {
                d[s | 1 << j][j] = d[s][i] + dis(w[i], w[j]);
                pre[s | 1 << j][j] = i;
              }
            }
          }
        }
      }
    }
    int pp = -1;
    rep(i, n) if (w[i] == p2) {
      pp = i;
      break;
    }
    vi path;
    int s = 1 << n;
    --s;
    while (pre[s][pp] != -1) {
      int np = pre[s][pp];
      s ^= 1 << pp;
      path.push_back(pp);
      pp = np;
    }
    reverse(all(path));
    return path;
  };
  vc<vi> ans1, ans2;
  cout << 8 << "\n";
  for (int i = 8; i >= 1; i--) { // bu, backup
    int x_ = bu[i][id].lstx;
    int y_ = bu[i][id].lsty;
    int s = bu[i][id].s;

    id = bu[i][id].lstid;
    int tx = bu[i - 1][id].lstx;
    int ty = bu[i - 1][id].lsty;

    // by graph = t[i-1]
    pii xx, yy;
    if (i - 1 > 0) {
      xx = t[i - 2][tx];
      yy = t[i - 2][ty];
    } else {
      xx = pii(7, 7);
      yy = pii(8, 8);
    }

    pii ex = t[i - 1][x_];
    pii ey = t[i - 1][y_];

    // start = xx, end with = ex
    // start = yy, end with = ey

    int tt = i - 1;
    vc<pii> x, y;
    vi xi, yi;
    rep(j, 20) if (s >> j & 1) x.pb(t[tt][j]), xi.pb(j);
    else y.pb(t[tt][j]), yi.pb(j);

    auto p1 = sol2(xx, x, ex);
    auto p2 = sol2(yy, y, ey);

    vi res1, res2;
    for (auto x : p1)
      res1.pb(xi[x]);
    for (auto y : p2)
      res2.pb(yi[y]);

    ans1.pb(res1);
    ans2.pb(res2);
  }

  reverse(all(ans1));
  reverse(all(ans2));

  rep(i, 8) {
    cout << ans1[i].size() << " " << ans2[i].size() << "\n";
    rep(j, ans1[i].size()) cout << ans1[i][j] << " ";
    cout << "\n";
    rep(j, ans2[i].size()) cout << ans2[i][j] << " ";
    cout << "\n";
  }

  double res = 0, d1 = 0, d2 = 0;
  pii p1 = pii(7, 7);
  pii p2 = pii(8, 8);
  rep(i, 8) {
    d1 = 0;
    d2 = 0;
    rep(j, ans1[i].size()) {
      d1 += dis(p1, t[i][ans1[i][j]]);
      p1 = t[i][ans1[i][j]];
    }
    rep(j, ans2[i].size()) {
      d2 += dis(p2, t[i][ans2[i][j]]);
      p2 = t[i][ans2[i][j]];
    }
    res += max(d1, d2);
  }

  cout << res << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    solve();
  }
  return 0;
}