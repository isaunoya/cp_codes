/*https://www.luogu.com.cn/blog/stoorz/hu-die-yu-hua-fou-dei-fou-shuo-di-gu-shi-ti-xie*/

#include<bits/stdc++.h>
#define inf 987654321
using namespace std;
int read(){
  bool f=1;
  int x=0;
  char c=getchar();
  while(c<'0'||c>'9'){
    if(c=='-')f=0;
    c=getchar();
  }
  while(c>='0'&&c<='9'){
    x=(x<<3)+(x<<1)-48+c;
    c=getchar();
  }
  return f?x:x*-1;
}
char cr[200];int tt;
inline void print(register int x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=2e6+5;
int t[maxn<<2],n,a[maxn],m;
set<int> s;
set<int>::iterator it;
inline void build(register int o,register int l,register int r){
  if(l==r){
    t[o]=a[l];
    return;
  }
  int mid=l+r>>1;
  build(o<<1,l,mid);
  build(o<<1|1,mid+1,r);
  t[o]=t[o<<1]+t[o<<1|1];
}
inline void change(register int o,register int l,register int r,register int q){
  if(l==r){
    t[o]=a[l];
    return;
  }
  int mid=l+r>>1;
  if(q<=mid) change(o<<1,l,mid,q);
  else change(o<<1|1,mid+1,r,q);
  t[o]=t[o<<1]+t[o<<1|1];
}
struct ask{
  int pos,sum;
};
inline ask query(register int o,register int l,register int r,register int sum,register int tar){
  if(l==r){
    ask tmp;
    tmp.sum=sum+t[o];
    tmp.pos=l;
    return tmp;
  }
  int mid=l+r>>1;
  if(sum+t[o<<1]>=tar) return query(o<<1,l,mid,sum,tar);
  else return query(o<<1|1,mid+1,r,sum+t[o<<1],tar);
}
void solve(){
  n=read();m=read();
  s.clear();
  for(register int i=1;i<=n;i++){
    a[i]=read();
    if(a[i]==1){
      s.insert(i);
    }
  }
  build(1,1,n);
  for(register int i=1;i<=m;i++){
    int ch=read();
    if(ch==2){
      int pos=read();
      if(a[pos]==1) s.erase(pos);
      a[pos]=read();
      if(a[pos]==1) s.insert(pos);
      change(1,1,n,pos);
    }
    else{
      int tar=read();
      if(tar==0||tar>t[1]){
        puts("NO");
        continue;
      }
      ask tmp=query(1,1,n,0,tar);
      int pos=tmp.pos;
      int sum=tmp.sum;
      while(sum<tar){
        pos++;
        sum+=a[pos];
      }
      if(sum==tar){
        puts("YES");
        continue;
      }
      int pos1=inf,pos2=inf,len=pos-1;
      if(s.begin()!=s.end()) pos1=*s.begin();
      it=s.lower_bound(pos);
      if(it!=s.end()) pos2=*it;
      if(pos1+len>n && pos2>n){
        puts("NO");
        continue;
      }
      if(pos1>=pos2-len){
        puts("YES");
        // print(pos2-len,' ');
        // print(pos2);
      }
      else{
        puts("YES");
        // print(pos1+1,' ');
        // print(pos1+len);
      }
    }
  }
}
signed main(){
  int t=read();
  while(t--){
    solve();
  }
  return 0;
}