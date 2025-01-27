#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;

void solve() {
	cin >> n;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll ans = 0;
	for (int i = 0; i < n; ++i) ans += a[i];
	while (a.size() > 1) {
		vector<ll> b;
		ll sm = 0;
		for (int i = 0; i + 1 < a.size(); ++i) {
			b.push_back(a[i + 1] - a[i]);
			sm += b.back();
		}
		ans = max(ans, abs(sm));
		swap(a, b);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}