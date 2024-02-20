#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<int> left(n);
	for (int i = 0; i < n; ++i) {
		if (i == 0) left[i] = -1;
		else {
			if (a[i] != a[i - 1]) left[i] = i - 1;
			else left[i] = left[i - 1];
		}
	}
	int q; cin >> q;
	while (q--) {
		int l, r; cin >> l >> r; --l; --r;
		if (left[r] >= l) {
			cout << left[r] + 1 << ' ' << r + 1 << '\n';
			continue;
		}
		else cout << -1 << ' ' << -1 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}