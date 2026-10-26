#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, q; cin >> n >> q;
	LL a[n], x[q];
	LL two[31]; memset(two, 0, sizeof(two));
	int last = 31;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < q; ++i) {
		cin >> x[i];
		if (x[i] < last) {
			for (int j = x[i]; j <= 30; ++j) two[j] += (1 << (x[i] - 1));
			last = x[i];
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 30; j >= 0; --j) {
			if (a[i] % (1 << j) == 0) {
				cout << a[i] + two[j] << ' ';
				break;
			}
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}