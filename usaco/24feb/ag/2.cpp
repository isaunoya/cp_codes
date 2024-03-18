#include<stdio.h>
#include<bits/stdc++.h>
#define fir first
#define sec second
#define all(x) begin(x),end(x)
using namespace std;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef __int128 int128;
typedef __uint128_t uint128;
typedef pair<int,int> pii;
template<typename type>
inline void chmin(type &x,const type &y)
{
	if(y<x)
		x=y;
}
template<typename type>
inline void chmax(type &x,const type &y)
{
	if(x<y)
		x=y;
}
constexpr int Max=1e5+10;
int n,m,len;
char a[Max],b[Max];
vector<pii>solve(char *a,char *b,int n,int m)
{
	vector<pii>ans;
	char x=0;
	while(n>1||m>1)
	{
//		cerr<<"a : ";
//		for(int i=1;i<=n;++i)
//			cerr<<a[i];
//		cerr<<"\n";
//		cerr<<"b : ";
//		for(int i=1;i<=m;++i)
//			cerr<<b[i];
//		cerr<<"\n";
//		cerr<<"x : "<<x<<"\n";
//		cerr<<"\n";
		if(a[n]==b[m])
		{
			if(n<m)
				ans.emplace_back(2,1),--m;
			else
				ans.emplace_back(1,2),--n;
		}
		else
		{
			if(!x)
			{
				if(n>1)
				{
					x=a[n],ans.emplace_back(1,3);
					--n;
				}
				else
				{
					x=b[m],ans.emplace_back(2,3);
					--m;
				}
			}
			else
			{
				if(a[n]==x)
				{
					if(n==1)
					{
						if(m>2)
						{
							ans.emplace_back(2,1);
							a[++n]=b[m],--m;
						}
						else
							ans.emplace_back(3,1),x=0;
					}
					else
						ans.emplace_back(1,3),--n;
				}
				else
				{
					if(m==1)
					{
						if(n>2)
						{
							ans.emplace_back(1,2);
							b[++m]=a[n],--n;
						}
						else
							ans.emplace_back(3,2),x=0;
					}
					else
						ans.emplace_back(2,3),--m;
				}
			}
		}
	}
	if(x)
	{
		if(a[n]==b[m])
		{
			ans.emplace_back(2,1);
			ans.emplace_back(3,2);
		}
		else
		{
			if(a[n]==x)
				ans.emplace_back(3,1);
			else
				ans.emplace_back(3,2);
		}
	}
	return ans;
}
void solve()
{
	int opt;
	cin>>len>>opt;
	n=m=0;
	char x;
	for(int i=1;i<=len;++i)
	{
		cin>>x;
		if(a[n]!=x)
			a[++n]=x;
	}
	for(int i=1;i<=len;++i)
	{
		cin>>x;
		if(b[m]!=x)
			b[++m]=x;
	}
	auto f=solve(a,b,n,m);
	auto g=solve(b,a,m,n);
	for(auto &[x,y]:g)
	{
		if(x<3)
			x=3-x;
		if(y<3)
			y=3-y;
	}
	if(f.size()>g.size())
		f.swap(g);
	cout<<f.size()<<"\n";
	if(opt!=1)
		for(auto [x,y]:f)
			cout<<x<<" "<<y<<"\n"; 
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
