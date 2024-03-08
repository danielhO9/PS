#include <bits/stdc++.h>
using namespace std;

int m, n;

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void Union(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	parents[x] = minn; parents[y] = minn;
}

void solve() {
	vector<int> parents(m + 1);
	for (int i = 1; i <= m; ++i) parents[i] = i;
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> Q;
	int ans = 0;
	while (n--) {
		int x, y, z; cin >> x >> y >> z;
		Q.push({z, {x, y}});
		ans += z;
	}
	while (!Q.empty()) {
		int z = Q.top().first, x = Q.top().second.first, y = Q.top().second.second; Q.pop();
		if (find(parents, x) != find(parents, y)) {
			ans -= z;
			Union(parents, x, y);
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> m >> n;
		if (m == 0 && n == 0) break;
		solve();
	}
}