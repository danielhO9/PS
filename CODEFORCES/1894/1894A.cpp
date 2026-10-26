#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	int awin = 0, bwin = 0;
	int win = -1;
	for (int i = 1; i <= n; ++i) {
		int atwin = 0, btwin = 0;
		int acnt = 0, bcnt = 0;
		for (int j = 0; j < n; ++j) {
			if (s[j] == 'A') ++acnt;
			else ++bcnt;
			if (acnt == i) {
				acnt = 0; bcnt = 0; ++atwin;
				win = 0;
			}
			if (bcnt == i) {
				acnt = 0; bcnt = 0; ++btwin;
				win = 1;
			}
		}
		if (acnt != 0 || bcnt != 0) continue;
		if (atwin > btwin && win == 0) {
			++awin;
		}
		else if (atwin < btwin && win == 1) {
			++bwin;
		}
	}
	if ((awin != 0 && bwin != 0) || (awin == 0 && bwin == 0)) {
		cout << '?' << '\n';
		return;
	}
	if (awin > 0) {
		cout << 'A' << '\n';
		return;
	}
	if (bwin > 0) {
		cout << 'B' << '\n';
		return;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}