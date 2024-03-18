#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int a = INF, b = INF, c = 0;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      if (a > b)
        swap(a, b);
      if (x > b) {
        a = x;
        c++;
      } else if (x <= a) {
        a = x;
      } else {
        b = x;
      }
    }
    cout << c << "\n";
  }
}