#include <bits/stdc++.h>
using namespace std;

void solve() {
	int a, b; cin >> a >> b;
	if (a % 2 == 0 && a / 2 != b) {
		cout << "YES\n";
		return;
	}
	if (b % 2 == 0 && b / 2 != a) {
		cout << "YES\n";
		return;
	}
	cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}