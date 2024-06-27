#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int x, y, k; cin >> x >> y >> k;
	while (true) {
		if (x < y) break;
		int m = x / y; m = (m + 1) * y;
		int dif = m - x;
		if (k < dif) {
			cout << x + k << '\n';
			return;
		}
		k -= dif;
		x += dif;
		while (x % y == 0) {
			x /= y;
		}
		if (k == 0) {
			cout << x << '\n';
			return;
		}
	}
	k %= (y - 1);
	x += k;
	x %= (y - 1);
	if (x == 0) x = y - 1;
	cout << x << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}