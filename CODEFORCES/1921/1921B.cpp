#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	string s, f; cin >> s >> f;
	int scnt = 0, bcnt = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '1' && f[i] == '0') ++scnt;
		if (s[i] == '0' && f[i] == '1') ++bcnt;
	}
	cout << min(scnt, bcnt) + abs(scnt - bcnt) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}