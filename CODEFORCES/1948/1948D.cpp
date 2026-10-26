#include <bits/stdc++.h>
using namespace std;

void solve() {
	int ans = 0;
	string s; cin >> s;
	int n = s.size();
	vector<int> cnt[27];
	vector<int> avail[n];
	for (int i = 0; i < n; ++i) {
		if (s[i] == '?') {
			cnt[26].push_back(i);
			for (int j = max(2 * i - n, 0); j < i; ++j) avail[j].push_back(i);
		} else {
			for (auto j: cnt[s[i] - 'a']) {
				if (j >= 2 * i - n) avail[j].push_back(i);
			}
			for (auto j: cnt[26]) {
				if (j >= 2 * i - n) avail[j].push_back(i);
			}
			cnt[s[i] - 'a'].push_back(i);
		}
	}
	// for (int i = 0; i < n; ++i) {
	// 	for (auto j: avail[i]) cout << j << ' ';
	// 	cout << '\n';
	// }
	for (int i = 0; i < n; ++i) {
		int sz = avail[i].size();
		for (int j = sz - 1; j >= 0; --j) {
			if (avail[i][j] - i <= ans) break;
			bool flag = true;
			for (int k = i; k < avail[i][j]; ++k) {
				if (s[k] != s[k + avail[i][j] - i] && s[k] != '?' && s[k + avail[i][j] - i] != '?') {
					flag = false;
					break;
				}
			}
			if (flag) {
				ans = max(ans, avail[i][j] - i);
				break;
			}
		}
	}
	cout << ans * 2 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}