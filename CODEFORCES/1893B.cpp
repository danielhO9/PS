#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m; cin >> n >> m;
	int a[n], b[m];
	vector<int> c;
	unordered_map<int, int> M;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) {
		c.push_back(a[i]);
		M[c[i]] = i;
	}
	for (int i = 0; i < m; ++i) cin >> b[i];
	// for (auto [i, j]: M) {
	// 	cout << i << ' ' << j << '\n';
	// }
	sort(b, b + m);
	sort(c.begin(), c.end());
	multiset<int, greater<int>> index[n + 1];
	for (int i = 0; i < m; ++i) {
		auto temp = lower_bound(c.begin(), c.end(), b[i]);
		if (temp == c.end()) {
			index[n].insert(b[i]);
		} else {
			index[M[*temp]].insert(b[i]);
		}
	}
	for (auto i: index[n]) {
		cout << i << ' ';
	}
	for (int i = 0; i < n; ++i) {
		cout << a[i] << ' ';
		for (auto j: index[i]) {
			cout << j << ' ';
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}