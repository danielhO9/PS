#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n - 1; ++i) cin >> a[i];
	int ans = 0;
	for (int i = 0; i < n - 1; ++i) ans += a[i];
	cout << -ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}