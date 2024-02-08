#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n, m, k; cin >> n >> m >> k;
	LL a[n], b[m], suma = 0, sumb = 0;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		suma += a[i];
	}
	for (int i = 0; i < m; ++i) {
		cin >> b[i];
		sumb += b[i];
	}
	sort(a, a + n); sort(b, b + m);
	if (a[0] < b[m - 1]) {
		suma += (b[m - 1] - a[0]);
		sumb -= (b[m - 1] - a[0]);
		swap(a[0], b[m - 1]);
	}
	if (k == 1) {
		cout << suma << '\n';
		return;
	}
	sort(a, a + n); sort(b, b + m);
	if (b[0] < a[n - 1]) {
		sumb += (a[n - 1] - b[0]);
		suma -= (a[n - 1] - b[0]);
		swap(b[0], a[n - 1]);
	}
	if (k == 2) {
		cout << suma << '\n';
		return;
	}
	sort(a, a + n); sort(b, b + m);
	if (a[0] < b[m - 1]) {
		suma += (b[m - 1] - a[0]);
		sumb -= (b[m - 1] - a[0]);
		swap(a[0], b[m - 1]);
	}
	if (k % 2 == 1) {
		cout << suma << '\n';
		return;
	}
	sort(a, a + n); sort(b, b + m);
	if (b[0] < a[n - 1]) {
		sumb += (a[n - 1] - b[0]);
		suma -= (a[n - 1] - b[0]);
		swap(b[0], a[n - 1]);
	}
	cout << suma << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}