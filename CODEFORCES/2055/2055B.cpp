#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[200000];
ll b[200000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	vector<ll> dif(n);
	ll cnt = 0;
	ll val = 0;
	for (int i = 0; i < n; ++i) {
		dif[i] = b[i] - a[i];
		if (dif[i] > 0) {
			++cnt;
			val = dif[i];
		}
	}
	if (cnt > 1) {
		cout << "NO\n";
		return;
	}
	if (cnt == 0) {
		cout << "YES\n";
		return;
	}
	// cout << val << '\n';
	for (int i = 0; i < n; ++i) {
		if (dif[i] <= 0 && dif[i] + val > 0) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}