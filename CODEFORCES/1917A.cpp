#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	int zcnt = 0, mcnt = 0, p = -1;
	for (int i = 0; i < n; ++i) {
		if (a[i] < 0) ++mcnt;
		if (a[i] == 0) ++zcnt;
		if (a[i] > 0) p = i + 1;
	}
	if (zcnt > 0) {
		cout << "0\n"; return;
	}
	if (mcnt % 2 == 0) {
		cout << "1\n";
		cout << 1 << ' ' << 0 << '\n';
		return;
	}
	cout << 0 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}