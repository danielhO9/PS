#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
ll a[200000];

void solve() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll maxa = 0ll;
	ll l = k, r = k;
	for (int i = 0; i < n; ++i) maxa = max(maxa, a[i]);
	// cout << maxa << ' ';
	for (int i = 0; i < n; ++i) {
		if (a[i] < maxa) {
			
			a[i] += ((maxa - a[i] + 2 * k - 1) / (2 * k)) * (2 * k);
			// cout << a[i] << ' ';
			if (a[i] > maxa + k) {
				l = min(l, a[i] - k - maxa);
			} else if (a[i] < maxa + k) {
				if (a[i] != maxa) {
					r = min(r, maxa + k - a[i]);
				}
			} else {
				l = 0ll;
				r = 0ll;
			}
		}
	}
	// cout << l << ' ' << r << '\n';
	r = k - r;
	if (l <= r) {
		cout << -1 << '\n';
	} else {
		cout << maxa + r << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}