#include <bits/stdc++.h>
#include <random>
#define rep(i, x) for (int i = 0; i < x; i++)

int a[10005];
int b[10005];

const int P = 998244353;
int power(int x, int y) {
	int r = 1;
	while (y) {
		if (y % 2 == 1) {
			r = 1ll * r * x % P;
		}

		y /= 2;
		x = 1ll * x * x % P;
	}

	return r;
}


mt19937 rng(time(NULL));
int main() {
	int n = rng() % 1005;
	int m = rng() % 1005;


	int r = 0;
	rep(i, n) {
		a[i] = rng() % 114514;
	}

	rep(i, m) {
		b[i] = rng() % 114514;
	}

	rep(i, n) {
		rep(j, m) {
			r ^= power(3, 1ll * a[i] * b[i] % (P - 1)) & 1;
		}
	}

	printf("%d %lld", r, 1ll * n * m % 2);
}