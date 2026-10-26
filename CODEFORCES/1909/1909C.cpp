#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	vector<pair<LL, int>> V;
	for (int i = 0; i < n; ++i) {
		LL t; cin >> t;
		V.push_back({t, 0});
	}
	for (int i = 0; i < n; ++i) {
		LL t; cin >> t;
		V.push_back({t, 1});
	}
	sort(V.begin(), V.end());
	vector<LL> pos;
	vector<int> temp;
	for (auto i: V) {
		if (i.second == 0) {
			temp.push_back(i.first);
		} else {
			pos.push_back(i.first - temp.back());
			temp.pop_back();
		}
	}
	sort(pos.begin(), pos.end(), greater<>());
	vector<LL> c(n); for (int i = 0; i < n; ++i) cin >> c[i];
	sort(c.begin(), c.end());
	LL ans = 0;
	for (int i = 0; i < n; ++i) ans += pos[i] * c[i];
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}