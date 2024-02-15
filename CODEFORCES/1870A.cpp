#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k, x; cin >> n >> k >> x;
	if (k - 1 > x) { cout << -1 << '\n'; return; }
	if (k > n) { cout << -1 << '\n'; return; }
	int ans = (k - 1) * k / 2;
	if (k == x) ans += (k - 1) * (n - k);
	else ans += x * (n - k);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}