#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, M, C;
  cin >> n >> M >> C;
  int N = 1;
  while (N <= n) {
  	N *= 2;
  }
  vector<vector<pair<int, int>>> g(N);
  for (int i = 0; i < M; i++) {
    int F, T, V;
    cin >> F >> T >> V;
    g[F].push_back(make_pair(T, V));
  }

  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < N; i++) {
      int u = i, v = i ^ (1 << j);
      if (v >= N) {
      	break;
      }
      g[u].push_back(make_pair(v, C * (1 << j)));
    }
  }

  vector<long long> d(N, INF);
  int A, B;
  cin >> A >> B;
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>>
      q;
  q.emplace(d[A] = 0, A);
  while (!q.empty()) {
    auto [dis, u] = q.top();
    q.pop();
    if (dis != d[u]) {
      continue;
    }
    for (auto [v, w] : g[u]) {
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        q.emplace(d[v], v);
      }
    }
  }

  cout << d[B] << "\n";
}