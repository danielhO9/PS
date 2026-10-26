#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;

void solve() {
	cin >> n >> m;
	vector<ll> a(n), b(m);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];
	multiset<ll> as, bs;
	for (int i = 0; i < n; ++i) as.insert(a[i]);
	for (int i = 0; i < m; ++i) bs.insert(b[i]);
	while (true) {
		while (!as.empty() && !bs.empty() && as.find(*bs.begin()) != as.end()) {
			ll tmp = *bs.begin();
			as.erase(as.find(tmp));
			bs.erase(bs.find(tmp));
		}
		while (!as.empty() && !bs.empty() && bs.find(*as.begin()) != bs.end()) {
			ll tmp = *as.begin();
			as.erase(as.find(tmp));
			bs.erase(bs.find(tmp));
		}
		if (as.empty() && bs.empty()) {
			cout << "YES\n";
			return;
		}
		if (as.empty() || bs.empty()) {
			cout << "NO\n";
			return;
		}

		if (*bs.begin() < *as.begin()) {
			cout << "NO\n";
			return;
		}

		ll tar = *bs.begin();
		bs.erase(bs.find(tar));
		ll f = tar / 2;
		ll s = tar - f;

		// cout << tar << ' ' << f << ' ' << s << '\n';
		if (as.find(f) != as.end()) {
			as.erase(as.find(f));
		} else bs.insert(f);

		if (as.find(s) != as.end()) {
			as.erase(as.find(s));
		} else bs.insert(s);

	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}