#include <bits/stdc++.h>
using namespace std;
int n, K;
const int N = 1e5 + 5;
int a[N];
bool aa[N][30];
vector<int> g[N];
int X, Y;
unsigned long long coef;

vector<int> del[N];
vector<int> stk;
void dfs(int u) {
  stk.push_back(u);
  if ((int)stk.size() >= K + 2) {
    int fa = stk[(int)stk.size() - 2 - K];
    del[fa].push_back(u);
  }
  for (auto v : g[u]) {
    dfs(v);
  }
  stk.pop_back();
}

unsigned long long ans[N];
int x[N][2][2];
void dfs2(int u) {
  x[u][aa[u][X]][aa[u][Y]] += 1;
  for (auto v : del[u]) {
    x[u][aa[v][X]][aa[v][Y]] -= 1;
  }
  for (auto v : g[u]) {
    dfs2(v);
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        x[u][j][k] += x[v][j][k];
      }
    }
  }
  for (int k = 0; k < 2; k++) {
    ans[u] += coef * x[u][0][k] * x[u][1][k ^ 1];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> K;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p;
    g[p].push_back(i);
  }
  dfs(1);
  for (int j = 0; j < 30; j++) {
    for (int i = 1; i <= n; i++) {
      aa[i][j] = a[i] >> j & 1;
    }
  }

  for (X = 0; X < 30; X++) {
    for (Y = X; Y < 30; Y++) {
      memset(x, 0, sizeof x);
      coef = 1ull << X + Y + (X != Y);
      dfs2(1);
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << ans[i] << "\n";
  }
}