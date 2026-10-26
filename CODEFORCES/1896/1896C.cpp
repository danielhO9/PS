#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, x; cin >> n >> x;
	vector<int> a(n), b(n);
	vector<pair<int, int>> V;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		V.push_back(make_pair(a[i], i));
	}
	for (int i = 0; i < n; ++i) cin >> b[i];
	sort(b.begin(), b.end());
	sort(V.begin(), V.end());
	int ans[n];
	for (int i = 0; i < x; ++i) {
		pair<int, int> temp = V[n - x + i];
		if (b[i] < temp.first) {
			ans[temp.second] = b[i];
		} else {
			cout << "NO" << '\n';
			return;
		}
	}
	for (int i = x; i < n; ++i) {
		if (b[i] >= V[i - x].first) {
			ans[V[i - x].second] = b[i];
		} else {
			cout << "NO" << '\n';
			return;
		}
	}
	cout << "YES" << '\n';
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}