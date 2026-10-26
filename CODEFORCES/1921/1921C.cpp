#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n, f, a, b; cin >> n >> f >> a >> b;
	vector<ll> m(n + 1, 0); for (int i = 1; i <= n; ++i) cin >> m[i];
	for (int i = 1; i <= n; ++i) {
		f -= min(b, a * (m[i] - m[i - 1]));
	}
	if (f > 0) {
		cout << "YES\n"; return;
	}
	cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}