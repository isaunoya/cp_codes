#include <bits/stdc++.h>
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
int N;
std::pair<int, int> t[1048576];
void build(const std::vector<int> &h, int l, int r, int p) {
  if (l == r)
    return t[p] = std::make_pair(h[l], l), void();
  int mid = (l + r) / 2;
  build(h, l, mid, p * 2);
  build(h, mid + 1, r, p * 2 + 1);
  t[p] = std::min(t[p * 2], t[p * 2 + 1]);
}
std::pair<int, int> query(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr)
    return t[p];
  int mid = (l + r) / 2;
  std::pair<int, int> res = std::make_pair(1e9, 1e9);
  if (ql <= mid)
    res = std::min(res, query(ql, qr, l, mid, p * 2));
  if (qr > mid)
    res = std::min(res, query(ql, qr, mid + 1, r, p * 2 + 1));
  return res;
}
i64 solve(const std::vector<int> &b, int l, int r) {
  if (l > r)
    return 0;
  int mid = query(l, r, 0, N - 1, 1).second;
  auto lv = solve(b, l, mid - 1);
  auto rv = solve(b, mid + 1, r);
  auto res = b[mid] + lv + rv;
  if (l > 0)
    res = std::max(res, rv);
  if (r < N - 1)
    res = std::max(res, lv);
  return res;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> N;
  std::vector<int> h(N);
  for (auto &t : h)
    std::cin >> t, --t;
  std::vector<int> b(N);
  for (auto &t : b)
    std::cin >> t;
  build(h, 0, N - 1, 1);
  std::cout << solve(b, 0, N - 1) << "\n";
  return 0;
}