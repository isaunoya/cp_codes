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
  int n;
  cin>>n;
  vc<array<int,3>> a(n);
  rp(i,n){
    string s;
    cin>>s;
    if(s=="add"){
      int x;
      cin>>x;
      a[i]=array<int,3>{1,x,0};//r+=x
    }else{
      int x, k;
      cin>>x>>k;
      --k;
      if(s=="beq"){
        a[i]=array<int,3>{2,x,k};
      }
      if(s=="bne"){
        a[i]=array<int,3>{3,x,k};
      }
      if(s=="blt"){
        a[i]=array<int,3>{4,x,k};
      }
      if(s=="bgt"){
        a[i]=array<int,3>{5,x,k};
      }
    }
  }
  // debug(a);
  auto id=[&](int i,int j){
    return i*256+j;
  };
  vi g((n+1)*256);
  rp(i,n){
    // debug(i,a[i]);
    rp(j,256){
      int u=id(i,j);
      if(a[i][0]==1){
        int v=id(i+1,(j+a[i][1])%256);
        g[u] = v;
      }
      if(a[i][0]==2){
        if(a[i][1]==j)g[u] = (id(a[i][2],j));
        else g[u] = (id(i+1,j));
      }
      if(a[i][0]==3){
        if(a[i][1]!=j)g[u] = (id(a[i][2],j));
        else g[u] = (id(i+1,j));
      }
      if(a[i][0]==4){
        if(j<a[i][1])g[u] = (id(a[i][2],j));
        else g[u] = (id(i+1,j));
      }
      if(a[i][0]==5){
        if(j>a[i][1])g[u] = id(a[i][2],j);
        else g[u] = (id(i+1,j));
      }
    }
  }
  // rp(i,(n+1)*256)if(sz(g[i]))debug(i,g[i]);
  queue<int>q;
  q.emplace(0);
  vi d((n+1)*256,-1);
  d[0]=0;
  while(!q.empty()){
    int u=q.front();q.pop();
    // debug(u);
    int v = g[u];
      if(d[v]==-1){
        d[v]=d[u]+1;
        q.emplace(v);
      }
    
  }
  bool ok=false;
  rp(i,256)if(d[id(n,i)]!=-1)ok=true;
  if(ok)cout<<"Yes\n";
  else cout<<"No\n";
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