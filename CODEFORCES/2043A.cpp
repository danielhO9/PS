#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;

void solve() {
	cin >> n;
	ll ans = 1ll;
	while (n > 3) {
		ans *= 2ll;
		n /= 4;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}