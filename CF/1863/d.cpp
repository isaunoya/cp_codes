#include <bits/stdc++.h>

#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

void solve() {
  int n,m;
  cin>>n>>m;
  vc<pii> a;
  vc<pii> b;
  rp(i,n)rp(j,m){
    char c;
    cin>>c;
    if(c=='U')
      a.pb(i,j);
    if(c=='L')
      b.pb(i,j);
  }
  vc<vi> ans(n,vi(m,-1));
  int c=0;
  int p=-1;
  for(auto [x,y]:a){
    if(x!=p){p=x,c^=1;}
    ans[x][y]=c;
    ans[x+1][y]=c^1;
    c^=1;
  }
  c=0;
  p=-1;
  sort(all(b),[&](auto A,auto B){
    return A.second<B.second;
  });
  for(auto [x,y]:b){
    if(y!=p){p=y,c^=1;}
    ans[x][y]=c;
    ans[x][y+1]=c^1;
    c^=1;
  }
  vi row(n),col(m);
  rp(i,n)rp(j,m){
    if(ans[i][j]==1){
      row[i]++;
      col[j]++;
    }else if(ans[i][j]==0){
      row[i]--;
      col[j]--;
    }
  }
  bool ok=true;
  rp(i,n)if(row[i])ok=false;
  rp(i,m)if(col[i])ok=false;
  if(!ok)cout<<"-1\n";
  else{
    rp(i,n){
      rp(j,m){
        if(ans[i][j]==1){
          cout<<'W';
        }else if(ans[i][j]==0){
          cout<<'B';
        }else{
          cout<<'.';
        }
      }
      cout<<"\n";
    }
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