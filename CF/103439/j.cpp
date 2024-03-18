#include <bits/stdc++.h>
using namespace std;
int n, res[4];
string s;
bool case1() {
  int G[4];
  memset(G, 0, sizeof(G));
  for (int i = 0; i < n * 3; i++)
    G[s[i] - 'A']++;
  int x = (G[0] < n) + (G[1] < n) + (G[2] < n);

  if (x > 1)
    return 0;
  char D = 0;
  for (int i = 0; i < 3; i++)
    res[i] = G[i];
  for (int i = 0; i < 3; i++)
    if (G[i] < n)
      D = i + 'A';
  res[s[0] - 'A']--;
  res[D - 'A']++;
  int r = 1;
  for (int i = 0; i < n * 3; i++) {
    while (res[D - 'A'] != n) {
      if (r == n * 3)
        break;
      res[s[r] - 'A']--;
      res[D - 'A']++;
      r++;
    }
    if (res[0] == res[1] && res[1] == res[2]) {
      cout << "1" << endl;
      cout << i + 1 << " " << r << " " << D << endl;
      return 1;
    }
    res[s[i] - 'A']++;
    res[D - 'A']--;
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  cin >> s;
  int A = count(s.begin(), s.end(), 'A');
  int B = count(s.begin(), s.end(), 'B');
  int C = count(s.begin(), s.end(), 'C');
  if (A == n && B == n && C == n) {
    cout << 0 << "\n";
    return 0;
  }

  int cnt[3];
  cnt[0] = cnt[1] = cnt[2] = 0;
  for (int i = 0; i < n * 3; i++) {
    int c = s[i] - 'A';
    cnt[c] += 1;
  }
  if (case1())
    return 0;

  cout << 2 << "\n";
  cnt[0] = cnt[1] = cnt[2] = 0;
  for (int i = 0; i < n * 3; i++) {
    int c = s[i] - 'A';
    cnt[c] += 1;
  }
  for (int i = 0; i < n * 3; i++) {
    int c = s[i] - 'A';
    cnt[c] -= 1;
    if (max({cnt[0], cnt[1], cnt[2]}) == n) {
      int p = 0;
      while (cnt[p] == n) {
        p += 1;
      }
      for (int j = 0; j <= i; j++) {
        s[j] = 'A' + p;
      }
      cout << 1 << " " << i + 1 << " " << char(p + 'A') << "\n";
      break;
    }
  }
  cnt[0] = cnt[1] = cnt[2] = 0;
  for (int i = 0; i < n * 3; i++) {
    int c = s[i] - 'A';
    cnt[c] += 1;
  }
  int p = min_element(cnt, cnt + 3) - cnt;
  for (int i = 0; i < n * 3; i++) {
    int c = s[i] - 'A';
    cnt[c] -= 1;
    s[i] = p;
    cnt[p] += 1;
    if (cnt[0] == n && cnt[1] == n && cnt[2] == n) {
      cout << 1 << " " << i + 1 << " " << char(p + 'A') << "\n";
      return 0;
    }
  }
}