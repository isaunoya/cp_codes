#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  string s;
  cin >> s;
  s += char(0);
  vector<vector<int>> lcp(N + 1, vector<int>(N + 1));
  for (int i = N - 1; i >= 0; i--) {
    for (int j = N - 1; j >= 0; j--) {
      if (s[i] == s[j]) {
        lcp[i][j] = lcp[i + 1][j + 1] + 1;
      }
    }
  }
  vector<int> P(N);
  iota(P.begin(), P.end(), 0);
  sort(P.begin(), P.end(), [&](int i, int j) {
    int a = i + lcp[i][j];
    int b = j + lcp[i][j];
    return s[a] < s[b];
  });
  vector<int> ans(N + 1);
  for (int L = 1; L <= N; L++) {
    vector<int> p;
    for (int i = 0; i < N; i++) {
      if (P[i] < N - L + 1) {
        p.emplace_back(P[i]);
      }
    }
    for (int i = 0, j = 0; i < N - L + 1; i = j) {
      j = i;
      while (j < N - L + 1 && lcp[p[i]][p[j]] >= L) {
        j++;
      }
      if (i < j)
        sort(p.begin() + i, p.begin() + j);
    }
    vector<int> rk(N - L + 1);
    for (int i = 0; i < N - L + 1; i++)
      rk[p[i]] = i;
    vector<int> stk, lft(N - L + 1, -1), rig(N - L + 1, N - L + 1);
    stk.clear();
    for (int i = 0; i < N - L + 1; i++) {
      while (!stk.empty() && rk[stk.back()] >= rk[i]) {
        stk.pop_back();
      }
      if (!stk.empty()) {
        lft[i] = stk.back();
      }
      stk.emplace_back(i);
    }
    stk.clear();
    for (int i = N - L; i >= 0; i--) {
      while (!stk.empty() && rk[stk.back()] >= rk[i]) {
        stk.pop_back();
      }
      if (!stk.empty()) {
        rig[i] = stk.back();
      }
      stk.emplace_back(i);
    }

    vector<int> add(N + 1);
    for (int i = 0; i < N - L + 1; i++) {
      auto check = [&](int k) {
        int l = max(i - (k - L) - 1, lft[i]);
        int r = min(i + k - L + 1, rig[i]);
        if (r - l >= k - L + 2) {
          return true;
        }
        return false;
      };
      int lo = L - 1, hi = N + 1;
      while (hi - lo > 1) {
        int m = (lo + hi) / 2;
        if (check(m)) {
          lo = m;
        } else {
          hi = m;
        }
      }
      add[lo] += 1;
    }
    int cur = 0;
    for (int K = N; K >= L; K--) {
      cur += add[K];
      ans[cur]++;
    }
  }
  for (int i = 1; i <= N; i++) {
    cout << ans[i] << "\n";
  }
  return 0;
}