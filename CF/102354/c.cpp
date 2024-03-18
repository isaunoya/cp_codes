#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  long long s = 0;
  priority_queue<pair<int, int>> q;
  vector<int> ans(n + m);
  // 0 resupplied
  // 1 declined
  // 2 approved
  for (int i = 0; i < n + m; i++) {
    int x;
    cin >> x;
    if (x >= 0) {
      ans[i] = 0;
      s += x;
    } else {
      int cost = -x;
      if (s >= cost) {
        s -= cost;
        ans[i] = 2;
        q.emplace(cost, i);
      } else if (!q.empty() && q.top().first > cost) {
        auto [lst, id] = q.top();
        q.pop();
        ans[id] = 1;
        ans[i] = 2;
        s += lst - cost;
        q.emplace(cost, i);
      } else {
        ans[i] = 1;
      }
    }
  }

  for (int i = 0; i < n + m; i++) {
    if (ans[i] == 0) {
      cout << "resupplied\n";
    } else if (ans[i] == 1) {
      cout << "declined\n";
    } else {
      cout << "approved\n";
    }
  }
}