#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n; vector<char> a(n);
	int pcnt = 0, mcnt = 0;
	for (int i = 0; i < n; ++i) {
		char c; cin >> c;
		if (c == '+') ++pcnt;
		else ++mcnt;
	}
	cout << abs(pcnt - mcnt) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}