#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[2 * n]; for (int i = 0; i < 2 * n; ++i) cin >> a[i];
	sort(a, a + 2 * n);
	cout << a[2 * n - 1] - a[n] + a[n - 1] - a[0] << '\n';
	for (int i = 0; i < n; ++i) {
		cout << a[i] << ' ' << a[i + n] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}