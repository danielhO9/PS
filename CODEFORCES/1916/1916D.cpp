#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	if (n == 1) {
		cout << 1 << '\n'; return;
	}
	string s[2] = {"169", "961"};
	int t = (n - 1) / 2;
	for (auto num: s) {
		for (int i = 0; i < t; ++i) {
			for (int j = 0; j < 3; ++j) {
				cout << num[j];
				if (j != 2) for (int k = 0; k < i; ++k) cout << '0';
			}
			for (int j = 0; j < (n - 3 - 2 * i); ++j) cout << '0';
			cout << '\n';
		}
	}
	cout << "196";
	for (int i = 0; i < n - 3; ++i) cout << '0';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}