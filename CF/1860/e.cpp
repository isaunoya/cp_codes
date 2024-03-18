#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  int n = s.size();

  std::vector<int> p[26][26];
  for (int i = 0; i < n - 1; i++) {
    p[s[i] - 'a'][s[i + 1] - 'a'].push_back(i);
  }

  std::vector dis(26, std::vector(26, std::vector(n - 1, -1)));
  for (int a = 0; a < 26; a++) {
    for (int b = 0; b < 26; b++) {
      if (!p[a][b].empty()) {
        std::queue<int> q;
        bool vis[26][26]{};
        vis[a][b] = true;
        for (auto i : p[a][b]) {
          dis[a][b][i] = 0;
          q.push(i);
        }

        while (!q.empty()) {
          int x = q.front();
          q.pop();

          if (x > 0 && dis[a][b][x - 1] == -1) {
            dis[a][b][x - 1] = dis[a][b][x] + 1;
            q.push(x - 1);
          }
          if (x < n - 2 && dis[a][b][x + 1] == -1) {
            dis[a][b][x + 1] = dis[a][b][x] + 1;
            q.push(x + 1);
          }

          int l = s[x] - 'a', r = s[x + 1] - 'a';
          if (!vis[l][r]) {
            vis[l][r] = true;
            for (auto i : p[l][r]) {
              if (dis[a][b][i] == -1) {
                dis[a][b][i] = dis[a][b][x] + 1;
                q.push(i);
              }
            }
          }
        }
      }
    }
  }

  int m;
  std::cin >> m;

  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    x--, y--;

    int ans = std::abs(x - y);
    for (int a = 0; a < 26; a++) {
      for (int b = 0; b < 26; b++) {
        if (!p[a][b].empty()) {
          ans = std::min(ans, dis[a][b][x] + dis[a][b][y] + 1);
        }
      }
    }
    std::cout << ans << "\n";
  }

  return 0;
}
