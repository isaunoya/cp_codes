#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
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
int ans = 1, x[500010*2], y[500010*2], Link[1000010], t,fla[500010*2];
struct edge {
  int v, nex;
} e[2000010*2];
bool vis[1000010*2],k;
map<pair<int, int>, int> mp;
void Insert(int xx, int yy) {
  e[++t].nex = Link[xx];
  e[t].v = yy;
  Link[xx] = t;
  return;
}
void dfs(int now) {
  vis[now] = true;
  for (int i = Link[now]; i; i = e[i].nex) {
    if (vis[e[i].v])
      continue;
    if (fla[e[i].v]) k=true;
    dfs(e[i].v);
  }
  return ;
}
void Solve() {
  ans = 1;
  int n;
  cin >> n;
  for (int i = 1; i <= 2 * n - 2; i++) {
    cin >> x[i] >> y[i];
    if (x[i]>y[i]) swap(x[i],y[i]);
    if (x[i] == y[i]) {
      ans = 0;
      return;
    }
    mp[make_pair(x[i], y[i])]++;
    if (mp[make_pair(x[i],y[i])]>2) {
      ans=0;
      return ;
    }
  }
  for (int i = 1; i <= 2 * n - 2; i++)
    if (mp[make_pair(x[i], y[i])] == 1) {
      Insert(y[i], x[i] + n);
      Insert(x[i] + n, y[i]);
    }
    else {
      fla[y[i]]++;fla[x[i]+n]++;
      if (fla[y[i]]>2||fla[x[i]+n]>2) {
        ans=0;
        return ;
      }
    }
  for (int i=1;i<=2*n-2;i++) 
    if (!vis[y[i]]&&mp[make_pair(x[i],y[i])]==2)  {
      k=false;dfs(y[i]);dfs(x[i]+n);
      if (k) {
        ans=0;
        return ;
      }
      else ans=2LL*ans%P;
    }
  for (int i = 2; i <= n; i++)
    if (!fla[i] && !vis[i]) {
      k=false;dfs(i);
      if (!k) ans = 2LL * ans % P;
    }
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Solve();
  cout << ans;
  return 0;
}