#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	if (a[0] == 1) {
		cout << "YES" << '\n';
	} else {
		cout << "NO" << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}