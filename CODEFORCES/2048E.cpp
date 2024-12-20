#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;

void solve() {
	cin >> n >> m;
	if (m > 2 * n - 1) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	vector<int> ans[2 * n];
	for (int i = 0; i < m; ++i) {
		int col = 1;
		for (int j = 0; j < n; ++j) {
			ans[(2 * j + i) % (2 * n)].push_back(col);
			ans[(2 * j + 1 + i) % (2 * n)].push_back(col);
			++col;
		}
	}
	for (int i = 0; i < 2 * n; ++i) {
		for (auto j: ans[i]) cout << j << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}