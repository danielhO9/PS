#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n, m; cin >> n >> m;
	vector<int> a(n);
	multiset<int> b; a[0] = m;
	for (int i = 1; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) { int t; cin >> t; b.insert(t); }
	// sort(a.begin(), a.end());
	LL ans = 0;
	for (int i = n - 1; i >= 1; --i) {
		auto ite = b.lower_bound(a[i] + 1);
		if (ite == b.end()) {
			++ans;
			b.erase(b.begin());
			continue;
		}
		b.erase(ite);
	}
	LL x = *b.begin();
	if (m < x) {
		cout << ans * m << '\n';
		return;
	}
	cout << ans * (x - 1) + (ans + 1) * (m - x + 1) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}