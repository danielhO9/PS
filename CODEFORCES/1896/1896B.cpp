#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	int fcnt = 0;
	int start = -1, end = n;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'A') {
			start = i;
			break;
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		if (s[i] == 'B') {
			end = i;
			break;
		}
	}
	if (start == -1 || end == n || start > end) {
		cout << 0 << '\n';
		return;
	}
	int cnt = 0;
	// for (int i = start; i < end; ++i) {
	// 	if (s[i] == 'B' && s[i + 1] == 'A') ++cnt;
	// }
	++cnt;
	cout << end - start + 1 - cnt << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}