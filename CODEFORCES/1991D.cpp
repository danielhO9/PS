#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	if (n == 1) {
		cout << "1\n1\n";
		return;
	}
	if (n == 2) {
		cout << "2\n1 2\n";
		return;
	}
	if (n == 3) {
		cout << "2\n1 2 2\n";
		return;
	}
	if (n == 4) {
		cout << "3\n1 2 2 3\n";
		return;
	}
	if (n == 5) {
		cout << "3\n1 2 2 3 3\n";
		return;
	}
	cout << 4 << '\n';
	for (int i = 1; i <= n; ++i) cout << i % 4 + 1 << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*



3
1 2 2 3
3
1 2 2 3 3
*/