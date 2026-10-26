#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1, n + 1); for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<vector<int>> cache(n + 1, vector<int> (n + 1, n + 1));
	bool vis[n + 2];
	for (int i = n; i >= 0; --i) {
		if (i != n) for (int j = 0; j <= n; ++j) cache[i][j] = cache[i + 1][j];
		memset(vis, 0, sizeof(vis));
		int mex = 0;
		for (int j = i; j <= n; ++j) {
			vis[a[j]] = true;
			while (vis[mex]) ++mex;
			cache[i][mex] = min(cache[i][mex], j);
		}
	}
	vector<int> ans(2 * n + 1, n + 1);
	ans[0] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= 2 * n; ++j) {
			if (ans[j] == i) {
				for (int k = 0; k <= n; ++k) ans[j ^ k] = min(ans[j ^ k], cache[i + 1][k]);
			}
		}
	}

	// ans[0] = 0;
	// priority_queue<pair<int, int>> pq;
	// pq.push(make_pair(0, 0));
	// while (!pq.empty()) {
	// 	int cost = -pq.top().first;
	// 	int here = pq.top().second;
	// 	pq.pop();
	// 	if (ans[here] < cost || cost >= n) continue;
	// 	for (int i = 0; i <= n; ++i) {
	// 		int there = here ^ i;
	// 		int nextDist = cache[cost + 1][i];
	// 		if (ans[there] > nextDist) {
	// 			ans[there] = nextDist;
	// 			pq.push(make_pair(-nextDist, there));
	// 		}
	// 	}
	// }
	for (int i = 2 * n; i >= 0; --i) if (ans[i] < n + 1) { cout << i << '\n'; return; }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
20
3 9 17 1 17 10 14 19 1 1 9 1 2 4 0 0 14 0 2 1
*/