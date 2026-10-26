#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	vector<int> cnt(n, 0);
	for (int i = 0; i < n; ++i) ++cnt[a[i]];
	bool flag = false;
	for (int i = 0; i < n; ++i) {

		if (cnt[i] == 0) {
			cout << i << '\n';
			return;
		}
		if (cnt[i] == 1) {
			if (flag == true) {
				cout << i << '\n';
				return;
			}
			flag = true;
		}

	}
	cout << 1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}