#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	vector<pair<int, int>> V;
	for (int i = 0; i < n; ++i) V.push_back({i + a[i] + 1, i});
	sort(V.begin(), V.end(), greater<pair<int, int>>());
	vector<int> inQ(n, 0);
	inQ[0] = 1; int f = 0, l = 1;
	priority_queue<pair<int, int>> Q;
	Q.push({a[V[0].second] + 1, 0});
	vector<int> ans;
	while (true) {
		int avail = ans.empty() ? V[f].first : min(ans.back() - 1, V[f].first);
		while (l < n && V[l].first >= avail) {
			Q.push({a[V[l].second] + 1, l});
			inQ[l] = 1; ++l;
		}
		while (Q.top().first > avail) {
			inQ[Q.top().second] = 2;
			Q.pop();
		}
		if (!Q.empty()) {
			inQ[Q.top().second] = 2;
			ans.push_back(avail);
			// cout << Q.top().second << ' ';
			Q.pop();
		}
		while (f < n && inQ[f] == 2) ++f;
		if (f == n) break;
		if (f == l) {
			inQ[f] = 1; ++l;
			Q.push({a[V[f].second] + 1, f});
		}
		// for (auto i: inQ) cout << i << ' ';
		// cout << '\n';
		// cout << f << ' ' << l << '\n';
	}
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}