#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n; cin >> n;
	unordered_map<LL, LL> M;
	LL a[n];
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		++M[a[i]];
	}
	vector<pair<LL, LL>> V;
	for (auto [i, j]: M) V.push_back({i, j});
	sort(V.begin(), V.end());
	int m = V.size();
	vector<LL> sum(m);
	for (int i = 0; i < m; ++i) {
		if (i == 0) sum[i] = V[i].second;
		else sum[i] = sum[i - 1] + V[i].second;
	}
	LL ans = 0;
	for (int i = 0; i < m; ++i) {
		LL t = V[i].second;
		if (i == 0) {
			if (t >= 3) ans += ((t * (t - 1) * (t - 2)) / 6LL);
		}
		else {
			if (t >= 3) ans += ((t * (t - 1) * (t - 2)) / 6LL);
			if (t >= 2) ans += ((t * (t - 1) / 2LL) * sum[i - 1]);
		}
	}
	cout << ans << '\n';
}

int main() {
	int t; cin >> t;
	while (t--) solve();
}