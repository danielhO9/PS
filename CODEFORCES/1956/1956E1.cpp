#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, a[200004];
bool rem[200004];

bool keepGo() {
	for (int i = 1; i <= n; ++i) if (a[i] && a[i % n + 1] && a[(i + 1) % n + 1] && a[(i + 2) % n + 1]) return true;
	return false;
}

void solve() {
	cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) rem[i] = false;
	if (n == 2) {
		while (a[1] && a[2]) {
			a[2] = max(0, a[2] - a[1]);
			a[1] = max(0, a[1] - a[2]);
		}
		rem[1] = a[1] > 0;
		rem[2] = a[2] > 0;
	} else if (n == 3) {
		while (a[1] && a[2] && a[3]) {
			a[2] = max(0, a[2] - a[1]);
			a[3] = max(0, a[3] - a[2]);
			a[1] = max(0, a[1] - a[3]);
		}
		rem[1] = a[1] && !a[3];
		rem[2] = a[2] && !a[1];
		rem[3] = a[3] && !a[2];
	} else {
		while (keepGo()) {
			for (int i = 1; i <= n; ++i) a[i % n + 1] = max(0, a[i % n + 1] - a[i]);
		}
		for (int i = 1; i <= n; ++i) {
			if (a[i] && a[i % n + 1]) a[i % n + 1] = max(0, a[i % n + 1] - a[i]);
			else break;
		}
		for (int i = 1; i <= n; ++i) if (!a[i] && a[i % n + 1]) {
			rem[i % n + 1] = true;
			ll x = a[i % n + 1], y = a[(i + 1) % n + 1], z = a[(i + 2) % n + 1];
			ll k = y / x;
			ll minus = y * k - x * k * (k + 1) / 2;
			if (minus < z) rem[(i + 2) % n + 1] = true;
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) if (rem[i]) ++cnt;
	cout << cnt << '\n';
	for (int i = 1; i <= n; ++i) if (rem[i]) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}