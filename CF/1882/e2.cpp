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
using namespace std;
const int INF = 1e9;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<int> sz(2);
  rep(i, 2) { cin >> sz[i]; }
  vector<vector<int>> perms(2);
  rep(i, 2) {
    perms[i].resize(sz[i]);
    for (auto &x : perms[i]) {
      cin >> x;
    }
    perms[i].insert(perms[i].begin(), 0);
  }
  vector<vector<int>> parity_best(2, {-1});
  int best_score = INF;
  rep(par, 2) {
    vector<vector<int>> best(2, {-1});
    rep(x, 2) {
      int N = perms[x].size();
      vector<int> goal(N);
      iota(goal.begin(), goal.end(), 0);

      rep(z, N) {
        vector<int> loc(N);
        vector<int> cur = perms[x];
        // loc_i is the position where value = i
        rep(i, N) { loc[cur[i]] = i; }
        vector<int> ops;
        auto swp = [&](int a, int b) {
          assert(a == loc[0]);
          ops.push_back((b - a + N) % N);
          swap(loc[cur[a]], loc[cur[b]]);
          swap(cur[a], cur[b]);
        };
        while (goal[loc[0]] != 0) {
          int a = loc[0];
          int b = loc[goal[a]];
          swp(a, b);
        }
        int ct = 0;
        while (ct < N) {
          if (cur[ct] == goal[ct]) {
            ct++;
            continue;
          }
          if (ct != loc[0]) {
            swp(loc[0], ct);
          }
          while (goal[loc[0]] != 0) {
            int a = loc[0];
            int b = loc[goal[a]];
            swp(a, b);
          }
        }
        if (ops.size() % 2 == par) {
          if (best[x] == vector<int>{-1} || ops.size() < best[x].size()) {
            best[x] = ops;
          }
        }
        rotate(goal.begin(), goal.begin() + 1, goal.end());
      }
    }
    if (best[0] == vector{-1}) {
      continue;
    }
    if (best[1] == vector{-1}) {
      continue;
    }
    rep(x, 2) {
      while (best[x].size() < best[!x].size()) {
        int N = perms[x].size();
        best[x].push_back(1);
        best[x].push_back(N - 1);
      }
    }
    int score = max(best[0].size(), best[1].size());
    if (score < best_score) {
      best_score = score;
      parity_best = best;
    }
  }

  if (best_score == INF) {
    cout << -1 << "\n";
    return 0;
  }
  cout << parity_best[0].size() << "\n";
  rep(i, parity_best[0].size()) {
    cout << parity_best[0][i] << " " << parity_best[1][i] << "\n";
  }
}