#include <bits/stdc++.h>
using namespace std;

int n;

void solution() {
	cin >> n;
	vector<pair<int, int>> a, b, c;
	int x;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		a.push_back({x, i});
	}
	for (int i = 0; i < n; ++i) {
		cin >> x;
		b.push_back({x, i});
	}
	for (int i = 0; i < n; ++i) {
		cin >> x;
		c.push_back({x, i});
	}
	sort(a.begin(), a.end(), greater<>());
	sort(b.begin(), b.end(), greater<>());
	sort(c.begin(), c.end(), greater<>());
	int ans = 0;
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) for (int k = 0; k < 3; ++k) {
		if ((a[i].second == b[j].second) || (c[k].second == b[j].second) || (a[i].second == c[k].second)) continue;
		ans = max(ans, a[i].first + b[j].first + c[k].first);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}