#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, x; cin >> n >> x;
	int a[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	vector<int> v;
	v.push_back(0);
	for (int i = 0; i < n; ++i) if (a[i] < x) v.push_back(a[i]);
	v.push_back(v.back() + 2 * (x - v.back()));
	int ans = 0;
	for (int i = 1; i < v.size(); ++i) {
		ans = max(ans, v[i] - v[i - 1]);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}