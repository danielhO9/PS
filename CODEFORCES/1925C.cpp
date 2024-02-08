#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k, m; cin >> n >> k >> m;
	string s; cin >> s;
	vector<bool> check(26);
	int cnt = 0;
	int cyc = 0;
	vector<char> ans;
	for (int j = 0; j < m; ++j) {
		if (check[s[j] - 'a'] == 0) {
			++cnt; check[s[j] - 'a'] = 1;
			if (cnt == k) {
				for (int i = 0; i < 26; ++i) check[i] = 0;
				++cyc;
				cnt = 0;
				ans.push_back(s[j]);
			}
		}
	}
	if (cyc >= n) {
		cout << "YES" << '\n';
		return;
	}
	cout << "NO" << '\n';
	for (auto i: ans) cout << i;
	for (int i = 0; i < k; ++i) {
		if (check[i] == 0) {
			for (int j = 0; j < n - cyc; ++j) cout << char(int('a') + i);
			cout << '\n';
			return;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}