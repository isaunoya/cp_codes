#include <bits/stdc++.h>
using namespace std;
int y;
int mon[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main() {
  cin >> y;
  //  if (y==2023) cout<<63;
  //  else {
  int now = 6;
  int s = 0;
  int ans = 0;
  if (y < 2023) {
    for (int i = y; i < 2023; i++)
      if ((i % 4 == 0) && (i % 100 != 0) || i % 400 == 0)
        s += 366;
      else
        s += 365;
    now = now - s % 7;
    now = (now + 7) % 7;
  } else if (y > 2023) {
    for (int i = 2023; i < y; i++)
      if ((i % 4 == 0) && (i % 100 != 0) || i % 400 == 0)
        s += 366;
      else
        s += 365;
    now = (now + s) % 7;
  }
  for (int i = 1; i <= 12; i++) {
    int x = mon[i];
    if (i == 2 && ((y % 4 == 0) && (y % 100 != 0) || y % 400 == 0))
      x++;
    if ((x + now) % 7)
      ans += (x + now) / 7 + 1;
    else
      ans += (x + now) / 7;
    now = (now + x) % 7;
  }
  cout << ans;
  //  }
  return 0;
}