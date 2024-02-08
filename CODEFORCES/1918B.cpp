#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n), b(n);
	vector<pair<int, int>> V;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		V.push_back({a[i], i});
	}
	for (int i = 0; i < n; ++i) {
		cin >> b[i];
	}
	sort(V.begin(), V.end());
	for (int i = 1; i <= n; ++i) cout << i << ' ';
	cout << '\n';
	for (int i = 0; i < n; ++i) {
		cout << b[V[i].second] << ' ';
	}
	cout << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}