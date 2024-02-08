#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n + 1]; for (int i = 1; i <= n; ++i) cin >> a[i];
	int index = 1;
	while (true) {
		if (index > n) break;
		for (int i = index + 2; i <= 2 * index; ++i) {
			if (i > n) break;
			if (a[i - 1] > a[i]) {
				cout << "NO" << '\n';
				return;
			}
		}
		index *= 2;
	}
	cout << "YES" << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}