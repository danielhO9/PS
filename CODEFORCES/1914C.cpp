#include <bits/stdc++.h>
using namespace std;

int a[200001], b[200001], k;

void solution() {
	int n; cin >> n >> k;
	a[0] = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	b[0] = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
		b[i] = max(b[i], b[i - 1]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (i > k) break;
		ans = max(ans, a[i] + b[i] * (k - i));
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}