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
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

const int P = 998244353;
void md(int &x) {
  if (x >= P) {
    x -= P;
  }
}
void solve() {
  int n, m;
  cin >> n >> m;
  vc<vi> a(n, vi(m));
  rep(i, n) rep(j, m) { cin >> a[i][j]; }
  rep(i, n) rep(j, m) {
    if (a[i][j] == -1)
      continue;
    if (a[i][j] <= i + j || a[i][j] > i + j + 2) {
      cout << 0 << "\n";
      return;
    }
  }
  auto b=a;
  rep(i,n)rep(j,m){
    if(a[i][j]==-1)b[i][j]=3;
    else{
      b[i][j]=a[i][j]-i-j;
    }
  }
  int ad=3;
  rep(i,n)rep(j,m)ad&=b[i][j];
  int ans=0;
  if(ad==1)ans=1;
  if(ad==2)ans=1;
  if(ad==3)ans=2;

  rep(i,n)rep(j,m){
    
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