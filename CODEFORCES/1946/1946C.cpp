#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k;

bool isAvail(int c, vector<vector<int>>&adj, vector<int> deg) {
	int cnt = 0;
	vector<int> dep(n + 1, 1);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
	for (int i = 1; i <= n; ++i) if (deg[i] == 1) {
		Q.push({1, i});
	}
	int rem = n;
	while (!Q.empty()) {
		int d = Q.top().first, now = Q.top().second; Q.pop();
		if (d >= c) {
			// cout << now << '\n';
			++cnt;
			rem -= d;
			if (cnt == k) {
				if (rem >= c) return true;
				else return false;
			}
		}
		else {
			for (auto i: adj[now]) dep[i] += d;
		}
		for (auto i: adj[now]) {
			--deg[i];
			if (deg[i] == 1) {
				Q.push({dep[i], i});
			}
		}
	}
	return false;
}

void solve() {
	cin >> n >> k;
	vector<vector<int>> adj(n + 1);
	vector<int> deg(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		++deg[u]; ++deg[v];
	}
	int l = 1, r = n / (k + 1), mid;
	while (l < r) {
		mid = (l + r + 1) / 2;
		if (isAvail(mid, adj, deg)) l = mid;
		else r = mid - 1;
	}
	cout << l << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}