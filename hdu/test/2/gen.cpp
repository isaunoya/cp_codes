#include <bits/stdc++.h>
#include <random>

using namespace std;

int n = 100000, q = 100000;
mt19937 rng(time(NULL));

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << n << " " << q << "\n";
  vector<int> Q(q);
  iota(Q.begin(), Q.end(), 0);
  shuffle(Q.begin(), Q.end(), rng);

  for (int i = 0; i < q; i++) {
    char c = '+';
    int x = rng() % n + 1;
    int y = rng() % n + 1;
    while (x == y) {
      x = rng() % n + 1;
    }
    cout << c << " ";
    cout << x << " " << y << " " << Q[i] + 1 << "\n";
  }

  return 0;
}