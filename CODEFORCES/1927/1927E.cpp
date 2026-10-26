#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	int num = 1;
	vector<int> ans(n);
	for (int i = 0; i < n; ++i) {
		if (num == n + 1) break;
		if (i % 2 == 0) {
			for (int j = i; j < n; j += k) ans[j] = num++;
		}
		else {
			for (int j = i + ((n - 1 - i) / k) * k; j >= i; j -= k) ans[j] = num++;
		}
		// for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
		// cout << '\n';
	}
	for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}