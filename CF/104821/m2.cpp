#include <bits/stdc++.h>

using namespace std;

using ll = long long;
void solve() {
	int n;
	cin >> n;
	ll a[n];
	for (int i = 0; i < n; i++) cin >> a[i];
	int q;
	cin >> q;
	ll f[n], g[n];
	while (q--) {
		int i, x;
		cin >> i >> x;
		--i;
		a[i] += x;
		ll res = 0;
		f[0] = a[0];

		for (int i = 1; i < n; i++) {
			f[i] = max(a[i], f[i - 1]);
		}

		g[n - 1] = a[n - 1];
		for (int i = n - 2; i >= 0; i--) {
			g[i] = max(a[i], g[i + 1]);
		}

		for (int i = 0; i < n; i++) {
			res += min(f[i], g[i]) - a[i];
		}

		cout << res << "\n";
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}