#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m, k; cin >> n >> m >> k;
	if (k < n + m - 2 || (k - (n + m - 2)) % 2 != 0) {
		cout << "NO" << '\n';
		return;
	}
	cout << "YES" << '\n';
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m - 1; ++j) {
			if (i == 0 && j == 0) cout << 'B' << ' ';
			else if (i == 0) {
				if (j % 2 == 0) cout << 'R' << ' ';
				else cout << 'B' << ' ';
			} else if (i == 1) {
				if (j % 2 == 0) cout << 'B' << ' ';
				else cout << 'R' << ' ';
			} else {
				cout << 'R' << ' ';
			}
		}
		cout << '\n';
	}
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m; ++j) {
			if (j == m - 1) {
				if ((i % 2) != (m % 2)) cout << 'R' << ' ';
				else cout << 'B' << ' ';
			} else {
				cout << 'R' << ' ';
			}
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}