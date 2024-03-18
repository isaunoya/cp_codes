#include <bits/stdc++.h>
using namespace std;

const int maxn = 60;
const int mod = 998244353;

int n, k;
int a[maxn];

int C[maxn][maxn];
int ans;
unordered_map<unsigned long long, int> mp[2][52], imm;
struct node {
  int kk;
  unsigned long long now;
};
queue<node> q[2];

bool pd(node fa, int i) {
  int dj = 0;
  for (; i <= n; i++) {
    unsigned long long pj = (fa.now + 1) & (~fa.now);
    if ((1ull << a[i] - 1) < pj)
      continue;
    int pp = imm[pj];
    dj += a[i] - pp;
    if (dj > fa.kk)
      return 0;
    fa.now += pj;
  }
  return 1;
}

int fast_pow(int now, int pw) {
  int ans = 1, dt = 1;
  while (dt <= pw) {
    if (dt & pw)
      ans = 1ll * ans * now % mod;
    dt <<= 1;
    now = 1ll * now * now % mod;
  }
  return ans;
}

int cnt = 0;
void dfs(int now, unsigned long long st, int num, int way) {
  if (now > n) {
    if (num != 0)
      return;
    int flag = imm.count(st + 1);
    if (!flag)
      return;
    ans += way;
    if (ans >= mod)
      ans -= mod;
  } else {
    for (int i = a[now]; i >= 1; i--) {
      if (a[now] - i > num)
        break;
      unsigned long long bt = st | (1ull << i - 1);
      int sz = num - (a[now] - i);
      int tms = 1ll * way * C[num][a[now] - i] % mod;
      int zz = (now + 1) & 1;
      if (now == n) {
        dfs(now + 1, bt, sz, tms);
        continue;
      }
      if (!pd((node){sz, bt}, now + 1))
        continue;
      if (mp[zz][sz].count(bt)) {
        mp[zz][sz][bt] = (mp[zz][sz][bt] + tms) % mod;
      } else {
        q[zz].push((node){sz, bt});
        mp[zz][sz][bt] = tms;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  n = 50, k = 50;
  // cin >> n >> k;
  for (int i = 0; i <= 50; i++) {
    unsigned long long u = 1ull << i;
    imm[u] = i + 1;
  }
  for (int i = 0; i <= k; i++) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; j++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
  }
  for (int i = 1; i <= n; i++)
    // cin >> a[i];
        a[i] = i;
  sort(a + 1, a + n + 1);
  mp[1][k][0] = 1;
  q[1].push((node){k, 0});
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= k; j++)
      mp[(i & 1) ^ 1][j].clear();
    // cnt=0;
    while (!q[i & 1].empty()) {
      // cnt++;
      node kd = q[i & 1].front();
      q[i & 1].pop();
      dfs(i, kd.now, kd.kk, mp[i & 1][kd.kk][kd.now]);
    }
    // cout<<cnt<<endl;
  }
  cout << 1ll * ans * fast_pow(fast_pow(n, k), mod - 2) % mod << endl;
  return 0;
}