#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) {
		if (i == 0) {
			if (a[i] >= 10) {
				if (a[i] / 10 <= a[i] % 10) a[i] %= 10;
			}
		} else {
			if (a[i] < a[i - 1]) {
				cout << "NO\n"; return;
			}
			if (a[i] < 10) {
				continue;
			} else {
				if (a[i] / 10 <= a[i] % 10 && a[i - 1] <= a[i] / 10) {
					a[i] %= 10;
				}
			}
		}
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}