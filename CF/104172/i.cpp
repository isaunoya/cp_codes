#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (int i = 0; i < a; i++)
#define rep2(i, a) for (int i = 0; i < a; i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define pb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  x = x < y ? x : y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  x = x > y ? x : y;
}
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
const double pi = std::acos(-1);
struct vector_t {
  double x, y;
  vector_t(double tempX = 0, double tempY = 0) { x = tempX, y = tempY; }
  vector_t rotate(double theta) {
    static double newX;
    static double newY;
    newX = x * std::cos(theta) - y * std::sin(theta);
    newY = y * std::cos(theta) + x * std::sin(theta);
    return vector_t(newX, newY);
  }
  bool operator <(const vector_t &rhs) const { return x * y < rhs.x * rhs.y; }
};


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<vector_t> point(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
    point[i] = vector_t(x, y);
  }
  auto solveOne = [&](const double &theta) ->double {
    double answer = 1e18;
    static std::vector<vector_t> vector(n);
    for (int i = 0; i < n; i++) {
      vector[i] = point[i].rotate(theta);
    }
    std::sort(vector.begin(), vector.end());
    auto distance = [&](const vector_t &x, const vector_t &y) -> double{
      return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y);
    };
    int ql = 0;
    for (int i = 0; i < n; i++) {
      if (i > 15)
        ++ql; 
      for (int j = ql; j < i; j++)
        answer = std::min(answer, distance(vector[i], vector[j]));
    }
    return answer;
  };
  double answer = 1e18;
  for (int theta = 0; theta < 360; theta += 60)
    answer = std::min(answer, solveOne(1. * theta / 180. * pi));
  std::cout << std::fixed << std::setprecision(4) << (long long) (answer + .5) << "\n";
  return 0;
}