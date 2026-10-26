#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	int l, r;
	for (int i = 0; i < n; ++i) {
		if (a[i] == 1) {
			l = i;
			break;
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		if (a[i] == 1) {
			r = i;
			break;
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] == 1) ++cnt;
	}
	cout << r - l + 1 - cnt << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}