#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, m; cin >> n >> m;
	string s, t; cin >> s >> t;
	bool good = true;
	for (int i = 0; i < n - 1; ++i) {
		if (s[i] == s[i + 1]) good = false;
	}
	if (good) {
		cout << "Yes" << '\n';
		return;
	}
	good = true;
	for (int i = 0; i < m - 1; ++i) {
		if (t[i] == t[i + 1]) good = false;
	}
	if (!good || t[0] != t[m - 1]) {
		cout << "No" << '\n';
		return;
	}
	vector<char> V;
	for (int i = 0; i < n - 1; ++i) {
		if (s[i] == s[i + 1]) V.push_back(s[i]);
	}
	for (auto i: V) {
		if (i == t[0]) {
			cout << "No" << '\n';
			return;
		}
	}
	cout << "Yes" << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}