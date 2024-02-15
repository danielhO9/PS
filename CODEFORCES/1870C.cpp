#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(n);
	vector<bool> visited(k + 1);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		visited[a[i]] = true;
	}
	vector<int> l(k + 1, -1); int maxa = 0;
	for (int i = 0; i < n; ++i) {
		if (maxa < a[i]) {
			for (int j = maxa + 1; j <= a[i]; ++j) l[j] = i;
			maxa = a[i];
		}
	}
	vector<int> r(k + 1); maxa = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (maxa < a[i]) {
			for (int j = maxa + 1; j <= a[i]; ++j) r[j] = i;
			maxa = a[i];
		}
	}
	for (int i = 1; i <= k; ++i) {
		if (l[i] == -1 || !visited[i]) cout << 0 << ' ';
		else cout << 2 * (r[i] - l[i] + 1) << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}