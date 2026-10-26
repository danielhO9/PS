#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, x; cin >> n >> x;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<bool> avail(n, true);

	int ans = 0;
	int tans = n;
	for (int i = 29; i >= 0; --i) {
		if (tans == 0) break;
		int val = (x >> i) & 1;
		int cnt = 0;
		for (int j = 0; j < n; ++j) {
			if ((a[j] >> i) & 1) ++cnt;
		}
		if (val == 0 && cnt % 2 == 1) break;
		if (val == 1 && cnt % 2 == 0) {
			int ttans = tans;
			int cnt = 0;
			for (int j = 0; j < n; ++j) {
				if ((a[j] >> i) & 1) ++cnt;
				if (cnt % 2 == 1 && avail[j]) {
					--ttans;
				}
			}
			ans = max(ans, ttans);
		} else if (val == 0) {
			int cnt = 0;
			for (int j = 0; j < n; ++j) {
				if ((a[j] >> i) & 1) ++cnt;
				if (cnt % 2 == 1 && avail[j]) {
					// cout << i << ' ' << j << '\n';
					--tans; avail[j] = false;
				}
			}
		}
		if (i == 0) ans = max(ans, tans);
	}
	if (ans == 0) cout << -1 << '\n';
	else cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
