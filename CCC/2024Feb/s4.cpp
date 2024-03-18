#include <bits/stdc++.h>
using namespace std;
int n, m;
int head[200005], to[400005], nxt[400005], cnt;
void add(int x, int y) {
  nxt[cnt] = head[x];
  to[cnt] = y;
  head[x] = cnt;
  cnt++;
}

int vis[200005], ans[200005];
void dfs(int x, int col) {
  vis[x] = 1;
  for (int i = head[x]; i != -1; i = nxt[i]) {
    int y = to[i];
    if (vis[y] == 1) {
      continue;
    } else {
      ans[i / 2] = col;
      dfs(y, 1 - col);
    }
  }
}

int main() {
  memset(head, -1, sizeof head);
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    add(x, y);
    add(y, x);
  }

  memset(ans, -1, sizeof ans);
  for (int i = 0; i < n; i++) {
    if (vis[i]) {
      continue;
    } else {
      dfs(i, 1);
    }
  }

  for (int i = 0; i < m; i++) {
    if (ans[i] == -1) {
      putchar('G');
      continue;
    } else {
      putchar(ans[i] ? 'R' : 'B');
    }
  }
}
