#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[500000];
ll lim[500000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (ll i = 0; i < n; ++i) {
		lim[i] = max(i * 2, (n - i - 1) * 2);
	}
	for (int i = 0; i < n; ++i) if (a[i] <= lim[i]) {
		cout << "No\n";
		return;
	}
	cout << "Yes\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}