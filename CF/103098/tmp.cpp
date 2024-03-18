#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 1000000007;
int main() {
#ifdef woshiluo
	freopen( "l.in", "r", stdin );
	freopen( "l.ans", "w", stdout );
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        i64 n;
        std::cin >> n;
        int a[6] = {1, 0, 0, P - 1}, b[7] = {1, P - 1, P - 2, P - 6, P - 1, 0, 1};
        while (n > 0) {
            int c[12] = {}, d[13] = {};
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 7; j++) {
                    c[i + j] = (c[i + j] + i64(a[i]) * (j % 2 == 0 ? b[j] : P - b[j])) % P;
                }
            }
            for (int i = 0; i < 6; i++) {
                a[i] = c[2 * i + n % 2];
            }
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    d[i + j] = (d[i + j] + i64(b[i]) * (j % 2 == 0 ? b[j] : P - b[j])) % P;
                }
            }
            for (int i = 0; i < 7; i++) {
                b[i] = d[2 * i];
            }
            n /= 2;
        }
        std::cout << a[0] << "\n";
    }
    return 0;
}
