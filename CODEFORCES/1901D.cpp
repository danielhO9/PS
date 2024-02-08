#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	int maxa[n], rmaxa[n];
	memset(maxa, 0, sizeof(maxa));
	memset(rmaxa, 0, sizeof(rmaxa));
	for (int i = 0; i < n; ++i) {
		maxa[i] = a[i] + (n - i - 1);
		rmaxa[i] = a[i] + i;
	}
	for (int i = 1; i < n; ++i) {
		maxa[i] = max(maxa[i - 1], maxa[i]);
	}
	for (int i = n - 2; i >= 0; --i) {
		rmaxa[i] = max(rmaxa[i + 1], rmaxa[i]);
	}
	int ans = INT32_MAX;
	for (int i = 0; i < n; ++i) {
		int cur = a[i];
		if (i > 0) cur = max(cur, maxa[i - 1]);
		if (i + 1 < n) cur = max(cur, rmaxa[i + 1]);
		ans = min(ans, cur);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}