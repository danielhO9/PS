#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

void solve() {
	cin >> n;
	if (n % 2 == 0) {
		cout << "Yes\n";
		for (int i = 0; i < n; ++i) {
			if (i % 2) cout << 1 << ' ';
			else cout << -1 << ' ';
		}
		cout << '\n';
	} else {
		int k = n / 2;
		if (k == 1) {
			cout << "No\n";
			return;
		}
		cout << "Yes\n";
		for (int i = 0; i < k; ++i) {
			cout << -(k-1) << ' ';
			cout << k << ' ';
		}
		cout << -(k - 1) << ' ';
		return;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}