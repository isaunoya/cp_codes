#include <bits/stdc++.h>
using namespace std;

int main() {
  set<array<int, 3>> s;

  int n, q;
  cin >> n >> q;

  auto solve = [&]() {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = i;
    }
    for (auto [z, x, y] : s) {
      swap(a[x], a[y]);
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
    	res += 1ll * (i + 1) * (a[i] + 1);
    }
    return res;
  };

  while (q--) {
    char c;
    cin >> c;
    int x, y, z;
    cin >> x >> y >> z;
    --x;
    --y;
    z = 1e9 - z;
    if (c == '+') {
      s.emplace(array<int, 3>{z, x, y});
    } else {
      s.erase(array<int, 3>{z, x, y});
    }
    cout << solve() << "\n";
  }
}