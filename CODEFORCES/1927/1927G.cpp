#include <bits/stdc++.h>
using namespace std;

int cache[101][101];
int a[101], n;

int matchCache(int l, int r) {
	if (l == r) return 0;
	if (r == l + 1) return 1;
	if (l + a[l] - 1 >= r - 1) return 1;
	if (r - a[r - 1] <= l) return 1;∑
	int& ret = cache[l][r];
	if (ret != -1) return ret;
	ret = 987654321;
	for (int i = l + 1; i < r; ++i) {
		ret = min(ret, matchCache(l, i) + matchCache(i, r));
	}
	bool avail = false;
	for (int i = l; i < r; ++i) {
		if (!avail) {
			if (i + a[i] >= r) avail = true;
		} else {
			if (i - a[i] + 1 <= l) ret = min(ret, 2);
		}
	}
	return ret;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n + 1; ++i) for (int j = 0; j < n + 1; ++j) cache[i][j] = -1;
	cout << matchCache(0, n) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}