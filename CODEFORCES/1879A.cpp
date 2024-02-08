#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int s[n], e[n];
	for (int i = 0; i < n; ++i) cin >> s[i] >> e[i];
	vector<int> V;
	for (int i = 1; i < n; ++i) {
		if (s[i] >= s[0]) V.push_back(e[i]);
	}
	sort(V.begin(), V.end());
	if (V.empty() || V.back() < e[0]) {
		cout << s[0] << '\n';
		return;
	}
	cout << -1 << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}