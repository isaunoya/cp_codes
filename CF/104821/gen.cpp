#include <algorithm>
#include <bits/stdc++.h>
#include <random>

mt19937 rng(time(NULL));

using namespace std;

int n = 1000, m = 1000;
void gen() {
	cout << n << "\n";
	for (int i = 0; i < n; i++) {
		int ai = rng() % 1000;
		cout << ai << " \n"[i + 1 == n];
	}

	cout << m << "\n";
	for (int i = 0; i < m; i++) {
		int pos = rng() % n + 1;
		int val = rng() % 1000;
		cout << pos << " " << val << "\n";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	int t = 10;
	cout << t << "\n";
	for (int i = 0; i < t; i++) {
		gen();
	}
}