#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, m; cin >> n >> m;
	vector<int> a(n);
	multiset<int> b; a[0] = 1;
	for (int i = 1; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) { int t; cin >> t; b.insert(t); }
	sort(a.begin(), a.end());
	int ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		auto ite = b.lower_bound(a[i] + 1);
		if (ite == b.end()) {
			++ans;
			b.erase(b.begin());
			continue;
		}
		b.erase(ite);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}