#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll lgcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return lgcd(b, a % b);
}

ll l, r, G;

void solve() {
	cin >> l >> r >> G;
	ll L = (l + G - 1) / G;
	ll R = r / G;
	ll d = R - L;
	if (d == 0) {
		if (L == 1) cout << G << ' ' << G << '\n';
		else cout << -1 << ' ' << -1 << '\n';
		return;
	}
	if (d < 0) {
		cout << -1 << ' ' << -1 << '\n';
		return;
	}
	while (true) {
		for (ll x = L; x + d <= R; ++x) {
			if (lgcd(x, d) == 1ll) {
				cout << x * G << ' ' << (x + d) * G << '\n';
				return;
			}
		}
		--d;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}