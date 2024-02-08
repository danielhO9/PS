#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> V;
	vector<bool> check(4, 0);
	for (int i = 0; i < n; ++i) {
		int x, y; cin >> x >> y;
		if (x > 0) check[0] = 1;
		if (y > 0) check[1] = 1;
		if (x < 0) check[2] = 1;
		if (y < 0) check[3] = 1;
	}
	if (check[0] && check[1] && check[2] && check[3]) cout << "NO" << '\n';
	else cout << "YES" << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}