#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k, x; cin >> n >> k >> x;
	int a[n + 1]; for (int i = 1; i <= n; ++i) cin >> a[i]; a[0] = 0;
	sort(a + 1, a + n + 1);
	int sum[n + 1];
	for (int i = 0; i <= n; ++i) {
		if (i == 0) sum[i] = a[i];
		else sum[i] = sum[i - 1] + a[i];
	}
	int ans = INT32_MIN;
	for (int i = 0; i <= k; ++i) {
		int tans = sum[n - i];
		int f = max(1, n - i - x + 1);
		tans -= 2 * (sum[n - i] - sum[f - 1]);
		ans = max(ans, tans);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}