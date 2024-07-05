#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int d[n], p[n];
	for (int i = 0; i < n; ++i) cin >> p[i] >> d[i];
	vector<pair<int, int>> v;
	for (int i = 0; i < n; ++i) v.push_back({d[i], p[i]});
	sort(v.begin(), v.end());
	int idx = v.size(); --idx;
	int ans = 0;
	priority_queue<int> q;
	for (int i = 10000; i >= 1; --i) {
		while (idx >= 0 && v[idx].first >= i) {
			q.push(v[idx].second);
			--idx;
		}
		if (!q.empty()) {
			ans += q.top();
			q.pop();
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}