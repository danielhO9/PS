#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	if (n % 2 == 1) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	char temp[2] = {'A', 'B'};
	for (int i = 0; i < n / 2; ++i) {
		cout << temp[i % 2];
		cout << temp[i % 2];
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}