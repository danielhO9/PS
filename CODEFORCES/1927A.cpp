#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	int l = -1, r = -1;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'B') {
			l = i; break;
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		if (s[i] == 'B') {
			r = i; break;
		}
	}
	if (l == -1) {
		cout << 0 << '\n'; return;
	}
	cout << r - l + 1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}