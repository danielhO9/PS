#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, k; cin >> n >> k;
	LL t = 1;
	LL b[n];
	for (int i = 0; i < n; ++i) {
		cin >> b[i];
		t *= b[i];
	}
	if (2023 % t != 0) {
		cout << "NO" << '\n';
		return;
	}
	cout << "YES" << '\n';
	for (int i = 0; i < k - 1; ++i) cout << 1 << ' ';
	cout << 2023 / t << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}