#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, x; cin >> n >> x;
	int ans = 0;
	int nn = n - x;
	for (int i = 1; i < 1e5; ++i) {
		if (i * i > nn) break;
		if (nn % i != 0) continue;
		if (i % 2 == 0 && (i + 2) / 2 >= x) ++ans;
		if (i * i == nn) break;
		int l = nn / i;
		if (l % 2 == 0 && (l + 2) / 2 >= x) ++ans;
	}
	if (x == 1) {
		cout << ans << '\n';
		return;
	}
	nn = n + x - 2;
	for (int i = 1; i < 1e5; ++i) {
		if (i * i > nn) break;
		if (nn % i != 0) continue;
		if (i % 2 == 0 && (i + 2) / 2 > x) ++ans;
		if (i * i == nn) break;
		int l = nn / i;
		if (l % 2 == 0 && (l + 2) / 2 > x) ++ans;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}