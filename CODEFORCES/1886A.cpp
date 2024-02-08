#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	if (n <= 6 || n == 9) {
		cout << "NO" << '\n';
		return;
	}
	if (n % 3 == 0) {
		cout << "YES" << '\n';
		cout << 1 << ' ' << 4 << ' ' << n - 5 << '\n';
	} else {
		cout << "YES" << '\n';
		cout << 1 << ' ' << 2 << ' ' << n - 3 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}