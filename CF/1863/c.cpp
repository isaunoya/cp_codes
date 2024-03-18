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
  int n,k;
  cin>>n>>k;
  vi a(n);
  rp(i,n)cin>>a[i];
  set<int>s;
  rp(i,n+2)s.insert(i);
  rp(i,n)if(s.count(a[i]))s.erase(a[i]);
    rp(j,n){
      int x=a[j];
      a[j]=*s.begin();
      s.erase(s.begin());
      s.insert(x);
    }
  a.pb(*s.begin());
  // debug(a);
  rp(i,n){
    cout<<a[((i-k+1)%(n+1)+n+1)%(n+1)]<<" \n"[i+1==n];
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