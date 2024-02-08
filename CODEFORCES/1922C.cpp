#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n; cin >> n;
	LL a[n + 1];
	for (int i = 1; i <= n; ++i) cin >> a[i];
	LL c[n + 1];
	for (int i = 1; i <= n; ++i) {
		if (i == 1) c[i] = 2;
		else if (i == n) c[i] = n - 1;
		else {
			if (a[i] - a[i - 1] < a[i + 1] - a[i]) c[i] = i - 1;
			else c[i] = i + 1;
		}
	}
	// for (int i = 1; i <= n; ++i) cout << c[i] << ' ';
	vector<LL> sum(n + 1), rsum(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (i == 1) sum[i] = 0;
		else {
			sum[i] = sum[i - 1];
			if (c[i - 1] == i) sum[i] += 1;
			else sum[i] += a[i] - a[i - 1];
		}
	}
	for (int i = n; i >= 1; --i) {
		if (i == n) rsum[i] = 0;
		else {
			rsum[i] = rsum[i + 1];
			if (c[i + 1] == i) rsum[i] += 1;
			else rsum[i] += a[i + 1] - a[i];
		}
	}
	int m; cin >> m;
	while (m--) {
		int x, y; cin >> x >> y;
		if (x < y) {
			cout << sum[y] - sum[x] << '\n';
		} else {
			cout << rsum[y] - rsum[x] << '\n';
		}
	}
}

int main() {
	int t; cin >> t;
	while (t--) solve();
}