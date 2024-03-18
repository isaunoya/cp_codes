/*
 * b.cpp 2023-09-30
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <array>
#include <map>
#include <queue>
#include <random>
#include <vector>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit(const char cur) { return cur >= '0' && cur <= '9'; } /*{{{*/
template <class T> T Max(T a, T b) { return a > b ? a : b; }
template <class T> T Min(T a, T b) { return a < b ? a : b; }
template <class T> void chk_Max(T &a, T b) {
  if (b > a)
    a = b;
}
template <class T> void chk_Min(T &a, T b) {
  if (b < a)
    a = b;
}
template <typename T> T read() {
  T sum = 0, fl = 1;
  char ch = getchar();
  for (; isdigit(ch) == 0; ch = getchar())
    if (ch == '-')
      fl = -1;
  for (; isdigit(ch); ch = getchar())
    sum = sum * 10 + ch - '0';
  return sum * fl;
}
template <class T> T pow(T a, ll p) {
  T res = 1;
  while (p) {
    if (p & 1)
      res = res * a;
    a = a * a;
    p >>= 1;
  }
  return res;
} /*}}}*/

const int mod = 1e9 + 7;

struct ModInt { /*{{{*/
  int32_t cur;
  ModInt(const int64_t _cur = 0) { cur = (((_cur % mod) + mod) % mod); }

  inline ModInt operator+(const ModInt &b) const { return (cur + b.cur) % mod; }
  inline ModInt operator-(const ModInt &b) const {
    return (((cur - b.cur) % mod) + mod) % mod;
  }
  inline ModInt operator*(const ModInt &b) const {
    return (1LL * cur * b.cur) % mod;
  }
  inline ModInt operator/(const ModInt &b) const {
    return (1LL * cur * pow(b, mod - 2).cur) % mod;
  }

  inline void operator+=(const ModInt &b) { (*this) = (*this) + b; }
  inline void operator-=(const ModInt &b) { (*this) = (*this) - b; }
  inline void operator*=(const ModInt &b) { (*this) = (*this) * b; }
  inline void operator/=(const ModInt &b) { (*this) = (*this) / b; }

  inline void output(const char end = '\n') { printf("%d%c", cur, end); }
}; /*}}}*/

const int32_t P = 1 << 9;

int32_t hash(const int32_t x, const int32_t y) { return (2 - y) * 3 + x; }
uint32_t full_pow(const uint32_t cur) { return 1 << cur; }
uint32_t set_bit(const uint32_t cur, const uint32_t pos) {
  return cur | full_pow(pos);
}
bool chk_pos(const uint32_t cur, const uint32_t pos) {
  return (cur >> pos) & 1;
}

ModInt f[P], orip[P][P];

const int LP = 24;
struct Matrix { /*{{{*/
  ModInt a[LP][LP];
  Matrix(const int cur = 0) {
    if (cur)
      for (int i = 0; i < LP; i++)
        a[i][i] = 1;
  }
  Matrix operator*(const Matrix &_b) const {
    Matrix res;
    for (int i = 0; i < LP; i++) {
      for (int j = 0; j < LP; j++) {
        for (int k = 0; k < LP; k++) {
          res.a[i][j] += a[i][k] * _b.a[k][j];
        }
      }
    }
    return res;
  }
  void operator*=(const Matrix &_b) { (*this) = (*this) * _b; }
} p; /*}}}*/

struct Node {
  int32_t x, y;
};
Node block[][3] = {
    {{0, 0}, {0, 1}, {0, 2}}, {{0, 0}, {1, 0}, {2, 0}},
    {{0, 0}, {0, 1}, {1, 0}}, {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}}, {{0, 1}, {1, 0}, {1, 1}},
};

int main() {
#ifdef woshiluo
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif
  std::vector<uint32_t> blocks;
  { /*{{{*/
    auto chk = [](const int32_t cur, const int32_t left, const int32_t rig) {
      return (cur >= left) && (cur < rig);
    };
    for (int o = 0; o < 6; o++) {
      const auto v = block[o];
      for (int i = 0; i < 3; i++) {
        int mask = 0;
        bool flag = true;
        for (int k = 0; k < 3; k++) {
          const auto node = v[k];
          if (chk(node.x + i, 0, 3)) {
            mask = set_bit(mask, hash(node.x + i, node.y));
            continue;
          }
          flag = false;
          break;
        }
        if (!flag)
          continue;
        blocks.push_back(mask);
      }
    }
  } /*}}}*/

  for (uint32_t sta = 0; sta < full_pow(12); sta++) { /*{{{*/
    bool flag = true;
    int mask = 0;
    for (int j = 0; j < 12; j++) {
      if (chk_pos(sta, j) == false)
        continue;
      if (mask & blocks[j])
        flag = false;
      mask |= blocks[j];
    }
    if (flag)
      f[mask] += 1;
  }
  /*}}}*/

  for (uint32_t i = 0; i < full_pow(6); i++) {
    for (uint32_t j = 0; j < full_pow(6); j++) {
      if (((j >> 3) & 7) < (i & 7))
        continue;
      const int32_t mask = ((7 ^ ((i >> 3) & 7)) << 6) |
                           ((((j >> 3) & 7) ^ (i & 7)) << 3) | ((j & 7));
      orip[i][j] += f[mask];
    }
  }

  std::vector<int> nums;
  for (uint32_t i = 0; i < full_pow(6); i++) {
    for (uint32_t j = 0; j < full_pow(6); j++) {
      if (orip[i][j].cur) {
        if (i != 0 && j != 0 &&
            (i <= 7 || std::__popcount(i) < 3 || std::__popcount(j) < 3)) {
          orip[i][j] = 0;
        } else {
          nums.push_back(i);
          nums.push_back(j);
#ifdef woshiluo
          printf("(%d,%d) = %3d\n", i, j, orip[i][j].cur);
#endif
        }
      }
    }
  }

  std::sort(nums.begin(), nums.end());
  nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
  auto find = [&nums](const int32_t cur) {
    return std::lower_bound(nums.begin(), nums.end(), cur) - nums.begin();
  };
  for (uint32_t i = 0; i < full_pow(6); i++) {
    for (uint32_t j = 0; j < full_pow(6); j++) {
      if (orip[i][j].cur) {
        p.a[find(i)][find(j)] = orip[i][j];
      }
    }
  }

  int T = read<int>();
  std::vector<std::pair<ll, int>> q;
  std::vector<ModInt> ans(T);
  for (int i = 0; i < T; i++) {
    q.push_back({read<ll>(), i});
  }
  std::sort(q.begin(), q.end());
  Matrix a;
  a.a[0][0] = 1;
  ll la = 0;
  for (auto &pair : q) {
    const auto diff = pair.first - la;
    la = pair.first;
    if (diff != 0)
      a = a * pow(p, diff);
    ans[pair.second] = a.a[0][0];
  }
  for (auto &x : ans)
    x.output();
}