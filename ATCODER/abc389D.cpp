#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll R;

void solve() {
	cin >> R;
	ll ans = 0;
	for (ll x = 1; x < R; ++x) {
		if (x * x + x + 2 >= R * R) break;
		ll l = 1, r = R, mid;
		while (l + 1 < r) {
			mid = (l + r) / 2;
			ll val = x * x + x + mid * mid + mid;
			if (val < R * R) l = mid;
			else r = mid;
		}
		// cout << mid << '\n';
		ans += l;
	}
	ans += R - 1;
	cout << ans * 4 + 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}