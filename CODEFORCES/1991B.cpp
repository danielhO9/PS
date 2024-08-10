#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int b[n - 1]; for (int i = 0; i < n - 1; ++i) cin >> b[i];
	int a[n]; memset(a, 0, sizeof(a));
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if ((b[j] >> i) & 1) {
				a[j] |= (1 << i);
				a[j + 1] |= (1 << i);
			}
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		if ((a[i] & a[i + 1]) != b[i]) {
			cout << -1 << '\n';
			return;
		}
	}
	for (int i = 0; i < n; ++i) cout << a[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}