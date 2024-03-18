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
#define fi first
#define se second

const int B2 = 1 << 24;
struct streambufcin {
  std::streambuf *in;
  char buf[B2], *bg, *ed, ch;
  streambufcin() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    in = std::cin.rdbuf();
    bg = ed = NULL;
  }
  char getchar() {
    return (bg == ed) && (ed = (bg = buf) + in->sgetn(buf, B2), bg == ed)
               ? -1
               : *bg++;
  }
  template <class T> streambufcin &operator>>(T &x) {
    bool neg = false;
    for (ch = getchar(); !isdigit(ch); ch = getchar())
      if (ch == '-')
        neg = true;
    for (x = 0; isdigit(ch); ch = getchar())
      x = x * 10 + ch - 48;
    if (neg)
      x = -x;
    return *this;
  }
} in;
struct streambufcout {
  std::streambuf *out;
  char buf[B2], *optr;
  streambufcout() {
    out = std::cout.rdbuf();
    optr = buf;
  }
  ~streambufcout() { flush(); }
  void flush() {
    out->sputn(buf, optr - buf);
    optr = buf;
  }
  void pc(char c) {
    if (optr == buf + B2)
      flush();
    *optr++ = c;
  }
  template <class T> streambufcout &operator<<(T x) {
    static int st[233], top;
    do {
      st[++top] = x % 10;
      x /= 10;
    } while (x);
    while (top)
      pc(st[top--] ^ 48);
    return *this;
  }
  streambufcout &operator<<(char c) {
    pc(c);
    return *this;
  }
} out;

const int B = 4000;
struct convex_hull {
  vc<pii> p;
  void clear() { p.clear(); }
  void pu(const int &x, const int &y) { p.pb(x, y); }
  ll cross(const pii &x, const pii &y) {
    return (ll)x.fi * y.se - (ll)x.se * y.fi;
  }
  void init() {
    sort(all(p), greater<pii>());
    vc<pii> t;
    for (const auto &value : p) {
      auto getcross = [&](auto x, auto y, auto z) {
        return cross(pii(y.fi - x.fi, y.se - x.se),
                     pii(z.fi - y.fi, z.se - y.se));
      };
      while (t.size() >= 2 &&
             getcross(t[sz(t) - 2], t[sz(t) - 1], value) <= 0) {
        t.pop_back();
      }
      t.pb(value);
    }
    p.swap(t);
  }
  ll get(const int &x) {
    auto evalueate = [&](int i) {
      if (i < 0 || i >= p.size()) {
        return 0LL;
      }
      return 1ll * x * p[i].first + p[i].second;
    };
    int l = -1, r = p.size();
    while (r - l > 2) {
      int m1 = (l + r) / 2;
      int m2 = m1 + 1;
      if (evalueate(m1) > evalueate(m2)) {
        r = m2;
      } else {
        l = m1;
      }
    }
    ll ans = 0;
    for (int i = l; i <= r; i++) {
      cmax(ans, evalueate(i));
    }
    return ans;
  }
};

void solve() {
  int N, Q;
  in >> N >> Q;
  vc<pii> P(N);
  for (int i = 0; i < N; i++) {
    in >> P[i].first >> P[i].second;
  }
  vc<array<int, 4>> querys(Q);
  for (int i = 0; i < Q; i++) {
    for (int j = 0; j < 4; j++) {
      in >> querys[i][j];
    }
    if (querys[i][0] == 1) {
      --querys[i][1];
    } else {
      --querys[i][2];
    }
  }
  vector<int> L, R;
  int cnt = 0;
  for (int i = 0; i < N; i += B) {
    L.pb(i);
    R.pb(min(i + B, N));
    cnt++;
  }
  vector<convex_hull> t(cnt);
  auto query = [&](int x, int l, int r) {
    ll ans = 0;
    for (int i = 0; i < cnt; i++) {
      if (R[i] <= l) {
        continue;
      }
      if (L[i] >= r) {
        continue;
      }
      if (l >= L[i] && r <= R[i]) {
        rep(j, l, r) { cmax(ans, 1ll * P[j].first * x + P[j].second); }
        continue;
      }
      if (l > L[i] && r >= R[i]) {
        rep(j, l, R[i]) { cmax(ans, 1ll * P[j].first * x + P[j].second); }
      } else if (l <= L[i] && r < R[i]) {
        rep(j, L[i], r) { cmax(ans, 1ll * P[j].first * x + P[j].second); }
      } else {
        cmax(ans, t[i].get(x));
      }
    }
    return ans;
  };

  for (int l = 0; l < Q; l += B) {
    int r = min(l + B, Q);
    vector<int> ban;
    for (int i = l; i < r; i++) {
      if (querys[i][0] == 1) {
        ban.push_back(querys[i][1]);
      }
    }
    sort(all(ban));
    ban.resize(unique(all(ban)) - ban.begin());
    for (int i = 0; i < cnt; i++) {
      t[i].clear();
      for (int j = L[i]; j < R[i]; j++) {
        if (!binary_search(all(ban), j)) {
          t[i].pu(P[j].first, P[j].second);
        }
      }
      t[i].init();
    }
    for (int i = l; i < r; i++) {
      if (querys[i][0] == 1) {
        int x = querys[i][1];
        int a = querys[i][2];
        int b = querys[i][3];
        P[x] = {a, b};
      } else {
        ll ans = 0;
        int x = querys[i][1];
        int ll = querys[i][2];
        int rr = querys[i][3];
        for (auto j : ban) {
          if (ll <= j && j < rr) {
            cmax(ans, 1ll * P[j].first * x + P[j].second);
          }
        }
        cmax(ans, query(x, ll, rr));
        out << ans << '\n';
      }
    }
  }
}

int main() {
  solve();
  return 0;
}