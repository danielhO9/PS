#include <bits/stdc++.h>
using namespace std;

void solve() {
	int x, y, k; cin >> x >> y >> k;
	if (y < x) {
		cout << x << '\n';
		return;
	}
	if (x + k >= y) {
		cout << y << '\n';
		return;
	}
	cout << 2 * y - x - k << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}