#include <bits/stdc++.h>
using namespace std;
const __int128 g = 3, p = 9223372036854775783ll;
char s[1232131];
pair<__int128, __int128> S[40];
map<pair<__int128, __int128>, int> op;
__int128 F[40];
int n;
__int128 pows(__int128 u, __int128 v) {
  __int128 ans = 1;
  while (v > 0) {
    if (v & 1)
      ans = ans * u % p;
    u = u * u % p, v = v >> 1;
  }
  return ans;
}
__int128 f(__int128 n) {
  if (pows(n, p / 2) != 1)
    return -1;
  return pows(n, (p + 1) / 4);
}
long long ans;
pair<__int128, __int128> inc(pair<__int128, __int128> A,
                             pair<__int128, __int128> B) {
  A.first = (A.first + B.first) % p;
  A.second = (A.second + B.second) % p;
  return A;
}
pair<__int128, __int128> sub(pair<__int128, __int128> A,
                             pair<__int128, __int128> B) {
  A.first = (A.first + p - B.first) % p;
  A.second = (A.second + p - B.second) % p;
  return A;
}
void dfs(int u, pair<__int128, __int128> sum) {
  if (u == n / 2 + 1) {
    op[sum]++;
    return;
  }
  dfs(u + 1, inc(sum, S[u]));
  dfs(u + 1, sub(sum, S[u]));
}
void dfs1(int u, pair<__int128, __int128> sum) {
  if (u == n + 1) {
    ans += op[sum];
    return;
  }
  dfs1(u + 1, inc(sum, S[u]));
  dfs1(u + 1, sub(sum, S[u]));
}
int main() {
  cin >> n;
  __int128 res = -1;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int j = 1; j <= len; j++)
      F[i] = (F[i] * 10ll + s[j] - '0') % p;
    if (f(F[i]) == res) {
      S[i].second = f(F[i] * 3 % p);
    } else
      S[i].first = f(F[i]);
    long long D = S[i].first;
  }
  dfs(2, S[1]);
  dfs1(n / 2 + 1, S[0]);
  cout << ans;
  return 0;
}