#include <bits/stdc++.h>

using namespace std;

vector<int> manacher(const string &s) {
  vector<int> p(s.size() * 2 + 2);
  string t = "~";
  t += "-";
  for (int i = 0; i < (int)s.size(); i++) {
    t += s[i];
    t += "-";
  }
  int n = (int)t.size();
  int m = -1, r = -1;
  for (int i = 0; i < n; i++) {
    if (i <= r) {
      p[i] = min(p[m * 2 - i], r - i + 1);
    }
    while (i - p[i] >= 0 && i + p[i] < n && t[i + p[i]] == t[i - p[i]]) {
      p[i] += 1;
    }
    if (i + p[i] > r) {
      r = i + p[i] - 1;
      m = i;
    }
    --p[i];
  }
  string().swap(t);
  return p;
}

const int N = 4e5 + 5;
const int inf = 1e9;

int t[N * 2];
void cmin(int &x, const int &y) {
  if (x > y)
    x = y;
}
void cmax(int &x, const int &y) {
  if (x < y)
    x = y;
}
void upd(int x, int v) {
  for (x += N; x; x >>= 1)
    cmin(t[x], v);
}
int query(int l, int r) {
  int res = inf;
  for (l += N, r += N; l < r; l /= 2, r /= 2) {
    if (l & 1)
      cmin(res, t[l++]);
    if (r & 1)
      cmin(res, t[--r]);
  }
  return res;
}

int pt[N];
vector<int> add[N];
void solve() {
  string s;
  cin >> s;
  int n = s.size();
  auto p = manacher(s);
  for (int i = 0; i < N * 2; i++)
    t[i] = inf;
  for (int i = 0; i < N; i++)
    add[i].clear();
  //  for(int x:p){
  //    cout<<x<<" ";
  //  }
  //  cout<<"\n";

  //  for(int i=1;i<n;i++){//[i-1,i]
  //    cout<<i<<" "<<p[2*i+1]<<"\n";
  //  }
  for (int i = 1; i < n; i++) {
    pt[i] = p[2 * i + 1] / 2;
    //    cout<<i<<" "<<pt[i]<<"\n";
  }
  //  cout<<"\n";
  int ans = 0;
  for (int i = 1; i < n; i++) {
    add[min(i + pt[i], n)].push_back(i);
  }
  for (int i = n; i >= 1; i--) {
    for (auto x : add[i])
      upd(x, x);
    int w = i - query(i - pt[i], i);
    //    cout<<" "<<query(i-pt[i],i)<<" "<<i<<"\n";
    cmax(ans, w);
  }
  cout << ans * 3 << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}