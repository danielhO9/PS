#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n, k, a, b; cin >> n >> k >> a >> b;
	vector<ll> x(n + 1), y(n + 1); for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
	ll amin = 1e14, bmin = 1e14;
	for (int i = 1; i <= k; ++i) {
		amin = min(amin, abs(x[i] - x[a]) + abs(y[i] - y[a]));
		bmin = min(bmin, abs(x[i] - x[b]) + abs(y[i] - y[b]));
	}
	ll ans = abs(x[b] - x[a]) + abs(y[b] - y[a]);
	ans = min(ans, amin + bmin);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}