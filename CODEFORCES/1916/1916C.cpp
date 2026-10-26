#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n; cin >> n;
	LL ecnt[n], ocnt[n], sum[n];
	LL a[n];
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		if (i == 0) {
			if (a[i] % 2 == 0) {
				ecnt[0] = 1;
				ocnt[0] = 0;
			} else {
				ecnt[0] = 0;
				ocnt[0] = 1;
			}
			sum[0] = a[0];
		} else {
			ecnt[i] = ecnt[i - 1];
			ocnt[i] = ocnt[i - 1];
			if (a[i] % 2 == 0) ++ecnt[i];
			else ++ocnt[i];
			sum[i] = sum[i - 1] + a[i];
		}
	}
	for (int i = 0; i < n; ++i) {
		LL ans = 0;
		ans += ocnt[i] / 3;
		if (i != 0 && ocnt[i] % 3 == 1) ++ans;
		cout << sum[i] - ans << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}