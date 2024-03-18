#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int id(int x, int y) { return x * m + y; }
void solve() {
  cin >> n >> m >> k;
  vector<tuple<int, int, string>> tuples;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      string s;
      cin >> s;
      if (s[0] == '-') {
        continue;
      } else {
        tuples.emplace_back(i, j, s);
      }
    }
  }
  vector<int> val(k + 1);
  for (int i = 0; i <= k; i++) {
    cin >> val[i];
  }
  int N = tuples.size();

  vector<vector<int>> coef(N, vector<int>(N));
  vector<vector<long long>> way1(N, vector<long long>(N));
  vector<vector<long long>> way2(N, vector<long long>(N));
  auto doit = [&](int ii, int jj, int x1, int y1, int x2, int y2) {
    long long &w1 = way1[ii][jj] = 0;
    long long &w2 = way2[ii][jj] = 0;
    if (x1 > x2) {
      swap(x1, x2), swap(y1, y2);
    }

    for (int i = x1; i <= x2; i++) {
      w1 |= 1LL << id(i, y1);
    }
    if (y1 < y2) {
      for (int j = y1; j <= y2; j++) {
        w1 |= 1LL << id(x2, j);
      }
    } else {
      for (int j = y1; j >= y2; j--) {
        w1 |= 1LL << id(x2, j);
      }
    }

    if (y1 < y2) {
      for (int j = y1; j <= y2; j++) {
        w2 |= 1LL << id(x1, j);
      }
    } else {
      for (int j = y1; j >= y2; j--) {
        w2 |= 1LL << id(x1, j);
      }
    }

    for (int i = x1; i <= x2; i++) {
      w2 |= 1LL << id(i, y2);
    }
  };

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i != j) {
        int cnt = 0;
        auto [x1, y1, s1] = tuples[i];
        auto [x2, y2, s2] = tuples[j];
        for (int l = 0; l < k; l++) {
          if (s1[l] == s2[l]) {
            cnt += 1;
          }
        }
        doit(i, j, x1, y1, x2, y2);
        way1[i][j] ^= 1LL << id(x1, y1);
        way1[i][j] ^= 1LL << id(x2, y2);

        way2[i][j] ^= 1LL << id(x1, y1);
        way2[i][j] ^= 1LL << id(x2, y2);

        coef[i][j] = val[cnt];
      }
    }
  }
  vector<int> bit(N);
  for (int i = 0; i < N; i++) {
    auto [x, y, s] = tuples[i];
    bit[i] = id(x, y);
  }

  unordered_map<long long, int> dp;
  auto dfs = [&](auto &dfs, long long state) -> int {
    if (dp.count(state)) {
      return dp[state];
    }
    int mx = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if ((state >> bit[i] & 1) && (state >> bit[j] & 1)) {
          int ok = 0;
          if ((state & way1[i][j]) == 0) {
            ok = 1;
          }
          if ((state & way2[i][j]) == 0) {
            ok = 1;
          }
          if (ok) {
            mx = max(mx, dfs(dfs, state ^ (1LL << bit[i]) ^ (1LL << bit[j])) +
                             coef[i][j]);
          }
        }
      }
    }
    return dp[state] = mx;
  };

  long long state = 0;
  for (int i = 0; i < N; i++) {
    state ^= 1LL << bit[i];
  }

  cout << dfs(dfs, state) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}