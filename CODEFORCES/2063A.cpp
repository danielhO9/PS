#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll l, r; cin >> l >> r;
	ll ans = r - l;
	// if (l == 1) ++ans;
	if (r == 1) {
		cout << 1 << '\n';
		return;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}