#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, k; cin >> n >> k;
	int a[n];
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i] %= k;
		if (a[i] == 0) a[i] = k;
	}
	int maxa = *max_element(a, a + n);
	if (maxa == k) {
		cout << 0 << '\n';
		return;
	}
	if (k == 4) {
		int odd = 0, even = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] % 2 == 1) ++odd;
			else ++even;
		}
		if (even >= 2) {
			cout << 0 << '\n';
			return;
		} else if (even == 1) {
			cout << 1 << '\n';
			return;
		} else {
			cout << min(k - maxa, 2) << '\n';
			return;
		}
	}
	cout << k - maxa << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}