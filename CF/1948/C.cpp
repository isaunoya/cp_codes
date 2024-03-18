#if defined(LOCAL)
#include <D:/cp/templates/my_template_compiled.hpp>
#else
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#define debug(...) 42
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
template <typename T> using vc = vector<T>;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second
#endif

void solve() {
  int N;
  cin>>N;
  vc<string>s(2);
  rep(i,2)cin>>s[i];
  int vis[2][N];
  rep(i,N)vis[0][i]=vis[1][i]=0;
  vector<pair<int,int>> que{{0,0}};
  vis[0][0]=1;
  rep(i,que.size()){
    auto[x,y]=que[i];
    rep(dx,-1,2){
      rep(dy,-1,2){
        if(dx*dx+dy*dy==1){
          int nx=x+dx;
          int ny=y+dy;
          if(0<=nx&&nx<2&&0<=ny&&ny<N){
            ny+=s[nx][ny]=='>'?1:-1;
            if(!vis[nx][ny]){
              vis[nx][ny]=1;
              que.emplace_back(nx,ny);
            }
          }
        }
      }
    }
  }
  cout<<(vis[1][N-1]?"YES":"NO")<<"\n";
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