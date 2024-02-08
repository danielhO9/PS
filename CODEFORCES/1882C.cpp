#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	LL a[n + 1]; for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<LL> plus;
	vector<LL> minus;
	bool flag = false;
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (flag) {
			if (a[i] > 0) ans += a[i];
			continue;
		}
		if (i % 2 == 1 && a[i] >= 0) {
			flag = true;
			ans += a[i]; continue;
		}
		if (i % 2 == 0 && a[i] <= 0) {
			flag = true;
			continue;
		}
		if (i % 2 == 0) plus.push_back(a[i]);
		else minus.push_back(a[i]);
	}
	int m = plus.size();
	for (int i = m - 2; i >= 0; --i) plus[i] += plus[i + 1];
	for (int i = 1; i < m; ++i) minus[i] = min(minus[i - 1], minus[i]);
	LL temp = 0;
	for (int i = 0; i < m; ++i) {
		temp = max(temp, plus[i] + minus[i]);
		if (i != 0) temp = max(temp, plus[i]);
	}
	cout << ans + temp << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}