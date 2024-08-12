#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll x, y, k; cin >> x >> y >> k;
	if (k % 2) {
		ll tmp = k / 2;
		for (int i = 0; i < k; ++i) {
			cout << x - tmp + i << ' ' << y - tmp + i << '\n';
		}
	} else {
		ll tmp = k / 2;
		ll xsum = 0ll, ysum = 0ll;
		for (int i = 0; i < k - 1; ++i) {
			cout << x - tmp + i << ' ' << y - tmp + i << '\n';
			xsum += x - tmp + i;
			ysum += y - tmp + i;
		}
		cout << x * k - xsum << ' ' << y * k - ysum << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}