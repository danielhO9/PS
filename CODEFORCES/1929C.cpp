#include <bits/stdc++.h>
using namespace std;

void solve() {
	int k, x, a; cin >> k >> x >> a;
	int now = 1, sum = 1;
	while (true) {
		if (x == 0) break;
		now = sum / (k - 1) + 1;
		sum += now;
		if (a < sum) {
			cout << "NO\n";
			return;
		}
		--x;
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}