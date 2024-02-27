#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, k; cin >> n >> k;
	int now = 1;
	int ans = 0;
	while (now + k - 1 <= n - k) {
		cout << "? " << now << endl;
		int q; cin >> q;
		ans ^= q;
		now += k;
	}
	if (now + k - 1 == n) {
		cout << "? " << now << endl;
		int q; cin >> q;
		ans ^= q;
		cout << "! " << ans << endl;
		return;
	}
	int y = (n - k + 1 + now) / 2;
	cout << "? " << now << endl;
	int q; cin >> q;
	ans ^= q;
	cout << "? " << y << endl;
	cin >> q;
	ans ^= q;
	cout << "? " << n - k + 1 << endl;
	cin >> q;
	ans ^= q;
	cout << "! " << ans << endl;
		return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}