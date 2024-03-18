#include <bits/stdc++.h>
#include <random>

using namespace std;

mt19937 rng(time(NULL));

const int INF = 10000000;
int n = 500, m = 5000;
void gen() {
	cout << n << " " << m << "\n";

	for (int i = 0; i < n; i++) {
		int val = rng() % INF;
		cout << val << " \n"[i + 1 == n];
	}
	for (int i = 0; i < m; i++) {
		int x = rng() % n + 1, r = rng() % INF;
		cout << x << " " << r << "\n";
	}
}

int main() {
	int t = 20;
	cout << t << "\n";
	for (int i = 0; i < t; i++) {
		gen();
	}
}