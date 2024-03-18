#include <bits/stdc++.h>
using namespace std;
int n,m,K,f[200010],tot=0;
vector< pair<int,int> > V[200010];
struct dsa
{
  int l,r,id;
}a[100010],tmp[100010];
int Calc(int l,int r,int ll,int rr)
{
  if (ll>r) return 0;
  if (rr<l) return 0;
  return min(r,rr)-max(l,ll)+1;  
}
int Get(int x) {return x==f[x]?x:f[x]=Get(f[x]);}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin>>n>>m>>K;
  if (m>2*K+1) {
    cout<<"NO";
    return 0;
  }
  for (int i=1;i<=K;i++) {
    int x1,x2,y;
    cin>>x1>>x2>>y;
    V[y].push_back(make_pair(x1,x2));
  }
  sort(V[1].begin(),V[1].end());
  int p=1;int num=0;
  for (int i=0;i<(int)V[1].size();i++) {
    if (V[1][i].first>p) a[++num]={p,V[1][i].first-1,++tot},f[tot]=tot;
    p=V[1][i].second+1;
  }
  if (p<=n) a[++num]={p,n,++tot};
  f[tot]=tot;
  for (int i=2;i<=m;i++) {
    sort(V[i].begin(),V[i].end());
    p=1;int nu=0;int k=1;
    for (int j=0;j<(int)V[i].size();j++) {
        if (V[i][j].first>p) {
            int L=p,R=V[i][j].first-1;
            tmp[++nu]={L,R,++tot};
            f[tot]=tot;
            while (k<=num&&a[k].r<L) k++;
            int val=Calc(L,R,a[k].l,a[k].r);
            while (k<=num&&val) {
                if (val>1) {
                  cout<<"NO";
                  return 0;
                }
                int fx=Get(a[k].id);
                if (fx==tot) {
                  cout<<"NO";
                  return 0;
                }
                f[fx]=tot;
                if (a[k].r>R) break;
                k++;val=Calc(L,R,a[k].l,a[k].r);
            }
        }
        p=V[i][j].second+1;
    }
    if (p<=n) {
      int L=p,R=n;
      tmp[++nu]={p,n,++tot};f[tot]=tot;
      while (k<=num&&a[k].r<L) k++;
      int val=Calc(L,R,a[k].l,a[k].r);
      while (k<=num&&val) {
            if (val>1) {
              cout<<"NO";
              return 0;
            }
            int fx=Get(a[k].id);
            if (fx==tot) {
              cout<<"NO";
              return 0;
            }
            f[fx]=tot;
            k++;val=Calc(L,R,a[k].l,a[k].r);
        }
    }
    for (int j=1;j<=nu;j++) a[j]=tmp[j];
    num=nu;
  }
  cout<<"YES";
  return 0;
}