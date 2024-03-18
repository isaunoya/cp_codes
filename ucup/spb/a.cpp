#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100005;
const int INF = 1e9;
int n;
char s[N];
int pres[N], prep[N];
int sufu[N], sufs[N];
int main() {
  scanf("%d", &n);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; i++) {
    pres[i] = pres[i - 1];
    prep[i] = prep[i - 1];
    if (s[i] == 's')
      pres[i] = i;
    if (s[i] == 'p')
      prep[i] = i;
  }
  sufu[n + 1] = sufs[n + 1] = n + 1;
  for (int i = n; i >= 1; i--) {
    sufu[i] = sufu[i + 1];
    sufs[i] = sufs[i + 1];
    if (s[i] == 'u')
      sufu[i] = i;
    if (s[i] == 's')
      sufs[i] = i;
  }
  int ans = INF;
  for (int i = 1; i <= n; i++)
    if (s[i] == 'b') {
      if (pres[prep[i]] >= 1 && sufu[sufs[i]] <= n) {
        //        cerr<<"now"<<i-1-prep[i]<<" "<<i-2-pres[prep[i]]<<"
        //        "<<sufs[i]-(i+1)<<" "<<sufu[sufs[i]]-(i+2)<<"\n";
        ans = min(ans, i - 1 - prep[i] + i - 2 - pres[prep[i]] + sufs[i] -
                           (i + 1) + sufu[sufs[i]] - (i + 2));
      }
    }
  printf("%d", ans);

  return 0;
}

/*
6
spbssu
*/