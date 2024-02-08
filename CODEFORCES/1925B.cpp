#include <bits/stdc++.h>
using namespace std;

void solve() {
	int x, n; cin >> x >> n;
	int ans = 1;
	for (int i = 1; i <= x; ++i) {
		if (i * i > x) break;
		if (x % i == 0) {
			if (x / i >= n) ans = max(ans, i);
			if (i >= n) ans = max(ans, x / i);
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}