#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool __hack = ios::sync_with_stdio(false);
auto __hack1 = cin.tie(nullptr);

template <typename T> T next() {
  T x;
  cin >> x;
  return x;
}

int64_t sum2(int64_t n) { return n * (n - 1) / 2; }

struct Segment {
  int l, r;
  int val;

  Segment() : l(0), r(0), val(0) {}

  Segment(int l, int r, int val) : l(l), r(r), val(val) {}

  int64_t eval(int64_t L, int64_t R) {
    if (val == 0) {
      return 0;
    }
    assert(l < L && R <= r + 1);
    int64_t ret = 0;
    // for (int i = L; i < R; ++i) {
    //     ret += int64_t(val) * (r - i);
    // }
    ret = int64_t(val) * ((R - L) * r - (sum2(R) - sum2(L)));
    return ret;
  }
};

struct SegmentTree {
  vector<int64_t> tree_sum;
  vector<Segment> tree_assign;
  int size;

  SegmentTree(int n) : size(1) {
    while (size < n) {
      size *= 2;
    }
    tree_sum.resize(2 * size - 1, 0);
    tree_assign.resize(2 * size - 1);
  }

  void assign(int l, int r, Segment s) {
    // cerr << "assign " << l << " " << r << " (" << s.l << ", " << s.r << ", "
    // << s.val << ")\n";
    assign(l, r, s, 0, 0, size);
  }

  int64_t assign(int l, int r, Segment s, int ti, int tl, int tr) {
    if (l <= tl && tr <= r) {
      tree_assign[ti] = s;
      return tree_sum[ti] = s.eval(tl, tr);
    }
    if (r <= tl || tr <= l) {
      return tree_sum[ti];
    }
    int tm = (tl + tr) / 2;
    if (tree_assign[ti].val != 0) {
      Segment push_down = tree_assign[ti];
      tree_assign[ti * 2 + 1] = push_down;
      tree_sum[ti * 2 + 1] = push_down.eval(tl, tm);
      tree_assign[ti * 2 + 2] = push_down;
      tree_sum[ti * 2 + 2] = push_down.eval(tm, tr);
      tree_assign[ti] = Segment();
    }
    return tree_sum[ti] = assign(l, r, s, ti * 2 + 1, tl, tm) +
                          assign(l, r, s, ti * 2 + 2, tm, tr);
  }

  int64_t query(int l, int r) {
    // cerr << "query " << l << " " << r << '\n';
    return query(l, r, 0, 0, size);
  }

  int64_t query(int l, int r, int ti, int tl, int tr) {
    if (l <= tl && tr <= r) {
      return tree_sum[ti];
    }
    if (r <= tl || tr <= l) {
      return 0;
    }
    if (tree_assign[ti].val != 0) {
      return tree_assign[ti].eval(max(l, tl), min(r, tr));
    }
    int tm = (tl + tr) / 2;
    return query(l, r, ti * 2 + 1, tl, tm) + query(l, r, ti * 2 + 2, tm, tr);
  }
};

int main() {
  int n = next<int>();
  int m = next<int>();
  int q = next<int>();
  SegmentTree tree(n + 1);
  vector<pair<int, int>> beacons(m);
  for (int i = 0; i < m; ++i) {
    beacons[i].first = next<int>();
  }
  for (int i = 0; i < m; ++i) {
    beacons[i].second = next<int>();
  }
  sort(beacons.begin(), beacons.end());
  for (int i = 0; i < m - 1; ++i) {
    tree.assign(
        beacons[i].first + 1, beacons[i + 1].first + 1,
        Segment(beacons[i].first, beacons[i + 1].first, beacons[i].second));
  }
  set<pair<int, int>> beacon_set;
  for (int i = 0; i < m; ++i) {
    beacon_set.insert(beacons[i]);
  }
  for (int i = 0; i < q; ++i) {
    int t = next<int>();
    if (t == 1) {
      int x = next<int>();
      int v = next<int>();
      auto beacon = make_pair(x, v);
      auto next_beacon = beacon_set.lower_bound(beacon);
      auto prev_beacon = next_beacon;
      prev_beacon--;
      tree.assign(
          prev_beacon->first + 1, beacon.first + 1,
          Segment(prev_beacon->first, beacon.first, prev_beacon->second));
      tree.assign(beacon.first + 1, next_beacon->first + 1,
                  Segment(beacon.first, next_beacon->first, beacon.second));
      beacon_set.insert(beacon);
    } else {
      int l = next<int>();
      int r = next<int>();
      cout << tree.query(l, r + 1) << '\n';
    }
  }
  return 0;
}
