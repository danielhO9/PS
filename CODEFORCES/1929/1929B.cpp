#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	if (k == 4 * n - 2) {
		cout << 2 * n << '\n';
		return;
	}
	cout << (k + 1) / 2 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}