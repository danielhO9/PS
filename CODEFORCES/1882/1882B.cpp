#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<vector<int>> S(n);
	vector<vector<int>> info(51);
	vector<int> cnt(51);
	for (int i = 0; i < n; ++i) {
		int m; cin >> m;
		for (int j = 0; j < m; ++j) {
			int t; cin >> t; S[i].push_back(t);
			info[t].push_back(i);
			++cnt[t];
		}
	}
	int ans = 0;
	for (int i = 1; i <= 50; ++i) {
		if (cnt[i] == 0) continue;
		vector<int> tcnt = cnt;
		for (auto j: info[i]) for (auto k: S[j]) --tcnt[k];
		int temp = 0;
		for (int i = 1; i <= 50; ++i) if (tcnt[i] > 0) ++temp;
		ans = max(ans, temp);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}