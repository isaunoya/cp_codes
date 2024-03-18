#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = 998244353, inv2 = (M + 1) >> 1;
struct Excrt {
  ll _gcd(ll a, ll b) {
    if (a < b)
      swap(a, b);
    while (b)
      a %= b, swap(a, b);
    return a;
  }
  ll _lcm(ll a, ll b) { return a / _gcd(a, b) * b; }
  ll slowmul(ll a, ll b, ll mod) {
    ll res = 0;
    a = (a % mod + mod) % mod, b = (b % mod + mod) % mod;
    for (; b; b >>= 1, (a <<= 1) %= mod)
      if (b & 1)
        (res += a) %= mod;
    return res;
  }
  void exgcd(ll &a, ll x, ll &b, ll y) // Lemma:abs(a)<=y,abs(b)<=x
  {
    if (y == 1) {
      a = 0;
      b = 1;
      return;
    } // a*(x%y)+a*(x/y)*y+b*y=c*y+d*(x%y)->a*(x/y)+b=c,a=d
    ll c, d;
    exgcd(c, y, d, x % y);
    a = d;
    b = c - a * (x / y); // abs(c)<=x%y,abs(d)<=y->abs(a)<=y,abs(b)<=x
  }
  pair<ll, ll> exgcdp(ll &a, ll x, ll &b, ll y,
                      ll c) // version which b doesn't matter
  {                         // ax+by=c if ok return 1/a/b else return 0
    // cout<<x<<'/'<<y<<'/'<<c<<'\n';
    ll g = _gcd(x, y); // now T(x)=y/gcd(x,y)
    if (c % g)
      return {0, 0};
    x /= g, y /= g, c /= g; // T(origin x)=now y=(*)T(x)
    if (!x)
      return {1, 0};
    x > y ? exgcd(a, x, b, y)
          : exgcd(b, y, a, x); // cout<<"x"<<x<<"y"<<y<<"a"<<a<<"b"<<b<<'\n';
    a = slowmul(a, c, y);
    return {y, a}; /*a*=c;b*=c;will overflow when max(a,b)^2>1e18)*/
  }
  pair<ll, ll> excrt(
      pair<ll, ll> pa,
      pair<ll, ll>
          pb) { // pa={a,c},pb={b,d}|t%a=c,t%b=d->ax%b=d-c,ax+by=d-c,(*)T(x)=b/gcd(a,b)
    if (!pa.first || !pb.first)
      return {0, 0};
    ll x, y; // t=ax+c<=a(*)T(x)+c,
    if (exgcdp(x, pa.first, y, pb.first, pb.second - pa.second) ==
        pair<ll, ll>{0, 0})
      return {0, 0};
    return {_lcm(pa.first, pb.first),
            pa.first * x + pa.second}; // x modified already
  }
} Exc;
struct S {
  bool jud[2] = {0, 0};
  ll res = M;
  ll x, y, bx, by, wx, wy;
  ll k, a, b;
  // bx+a*dx=k*x
  ll tran(ll a, ll b) {
    if (a <= b)
      return 0;
    a--;
    return a / b;
  }
  void solve() {
    cin >> x >> y >> wx >> wy >> bx >> by;
    if (wx > bx)
      wx = x - wx, bx = x - bx, jud[0] = 1;
    if (wy > by)
      wy = y - wy, by = y - by, jud[1] = 1;
    ll dy = by - wy, dx = bx - wx, g = Exc._gcd(dy, dx);
    dy /= g, dx /= g;
    ll Rx = bx, Ry = by;
    x /= 2;
    bx %= x;
    auto p1 = Exc.exgcdp(a, dx, b, x, (x - bx) % x);
    auto p2 = Exc.exgcdp(a, dy, b, y, (y - by) % y);
    // cout<<p1.first<<','<<p1.second<<"|"<<p2.first<<','<<p2.second<<"\n";//return;
    auto p3 = Exc.excrt(p1, p2);
    if (p3 == pair<ll, ll>{0, 0}) {
      cout << "-1\n";
      return;
    }
    // cout<<p3.first<<"/"<<p3.second<<'\n';
    dy *= p3.second, dx *= p3.second;
    ll Fy = dy + Ry, Fx = dx + Rx; // cout<<Fy<<'/'<<Fx<<'\n';
    x *= 2;
    ll b_c = tran(Fy, y) + tran(Fx, x);
    // cout<<jud[0]<<"&"<<jud[1]<<'\n';
    ll F2y = Fy % (y * 2);
    ll F2x = Fx % (x * 2);
    if (F2x > x)
      F2x -= x;
    // Fy%=y;if(jud[1])Fy=y-Fy;
    // cout<<b_c<<' '<<F2x<<' '<<F2y<<'\n';
    if (jud[0])
      F2x = x - F2x;
    if (jud[1])
      F2y = y - F2y;
    cout << b_c << ' ' << F2x << ' ' << F2y << '\n';
    // if(p1=={0,0}){cout<<"-1\n";return;}
  }
};
void precal() {}
int main() {
  // freopen("1.in","r",stdin);
  // cout<<fixed<<setprecision(12);
  ios::sync_with_stdio(0);
  cin.tie(0);
  precal();
  int t = 1;
  cin >> t;
  // clock_t a=clock();
  while (t--) {
    S SS;
    SS.solve();
  }
  // cout<<"Time:"<<double(clock()-a)<<'\n';
}