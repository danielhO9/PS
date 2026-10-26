#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m, k; cin >> n >> m >> k;
	if (k > 3) {
		cout << 0 << '\n';
	} else if (k == 3) {
		if (n >= m || n == 1) cout << 0 << '\n';
		else {
			int ans = m; ans -= n - 1;
			ans -= m / n;
			cout << ans << '\n';
		}
	} else if (k == 2) {
		if (m == 0) {
			cout << 0 << '\n';
		}else {
			int ans = min(n, m);
			if (n >= m) cout << ans << '\n';
			else {
				ans += m / n; --ans;
				cout << ans << '\n';
			}
		}
	} else {
		cout << 1 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}