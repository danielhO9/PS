#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n, k; cin >> n >> k;
	vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<ll> x(n); for (int i = 0; i < n; ++i) cin >> x[i];
	vector<ll> suma(n + 1, 0);
	for (int i = 0; i < n; ++i) suma[abs(x[i])] += a[i];
	for (int i = 1; i <= n; ++i) suma[i] += suma[i - 1];
	for (int i = 1; i <= n; ++i) {
		if (suma[i] > k * i) {
			cout << "NO\n"; return;
		}
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}