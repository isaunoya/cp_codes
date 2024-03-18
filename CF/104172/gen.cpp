#include <bits/stdc++.h>
#include <cstdio>
#include <random>
using namespace std;
mt19937 rng(time(NULL));

int main() {

	freopen(".in", "w", stdout);
	int t = 1000;
	cout << t << "\n";
	for (int i = 0; i < t; i++) {
		cout << rng() % 1000 + 1 << " " << rng() % 1000 + 1 << "\n";
	}
}