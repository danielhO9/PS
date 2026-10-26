#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, k; cin >> n >> k;
	vector<LL> a(n);
	vector<LL> tosort(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		tosort[i] = a[i];
	}
	if (k >= 3) {
		cout << 0 << '\n';
		return;
	}
	LL ans = *min_element(a.begin(), a.end());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) if (i != j) {
			ans = min(ans, abs(a[i] - a[j]));
		}
	}
	if (k == 1) {
		cout << ans << '\n';
		return;
	}
	sort(tosort.begin(), tosort.end());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) if (i != j) {
			LL value = abs(a[i] - a[j]);
			auto ite = lower_bound(tosort.begin(), tosort.end(), value);
			// cout << value << ' ' << *ite << '\n';
			if (ite != tosort.end()) ans = min(ans, (*ite) - value);
			if (ite != tosort.begin()) {
				--ite;
				ans = min(ans, value - (*ite));
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}