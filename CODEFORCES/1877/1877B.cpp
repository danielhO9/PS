#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n, p; cin >> n >> p;
	LL a[n], b[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	vector<pair<LL, LL>> V;
	for (int i = 0; i < n; ++i) V.push_back({b[i], a[i]});
	sort(V.begin(), V.end());
	LL ans = p, cnt = 1;
	for (int i = 0; i < n; ++i) {
		if (cnt == n || V[i].first >= p) break;
		if (cnt + V[i].second > n) {
			ans += (n - cnt) * V[i].first;
			cnt = n;
		} else {
			ans += V[i].first * V[i].second;
			cnt += V[i].second;
		}
	}
	ans += (n - cnt) * p;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}