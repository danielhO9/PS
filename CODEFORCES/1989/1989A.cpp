#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) {
		int x, y; cin >> x >> y;
		if (y > 0) {
			cout << "YES\n";
		} else {
			if (y >= -1) cout << "YES\n";
			else cout << "NO\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}