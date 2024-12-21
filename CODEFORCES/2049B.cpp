#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
string s;

void solve() {
	cin >> n;
	cin >> s;
	int ls = -1;
	for (int i = 0; i < n; ++i)
		if (s[i] == 's') {
			ls = i;
		}
	if (ls == -1) {
		cout << "YES\n";
		return;
	}
	int fp = -1;
	for (int i = 0; i < n; ++i)
		if (s[i] == 'p') {
			fp = i;
			break;
		}
	if (fp == -1) {
		cout << "YES\n";
		return;
	}
	if (fp != n - 1 && ls != 0) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	return;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}