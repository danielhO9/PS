#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
ll a[200000];

void solve() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, a + n);
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		if (i % 2 == 0) ans += a[n - 1 - i];
		else {
			ll dif = a[n - i] - a[n - 1 - i];
			dif = min(dif, k);
			k -= dif;
			a[n - 1 - i] += dif;
			ans -= a[n -1  - i];
		}
	}

	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}