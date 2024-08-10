#include <bits/stdc++.h>
using namespace std;

int n, m, k;

int p[1001];

int find(int v) {
	if (p[v] == v) return v;
	p[v] = find(p[v]);
	return p[v];
}

void Union(int v, int u) {
	v = find(v), u = find(u);
	if (v == u) return;
	p[v] = u;
}

void solve() {
	for (int i = 1; i <= n; ++i) p[i] = i;
	vector<pair<int, int>> b, r;
	for (int i = 0; i < m; ++i) {
		char c; int v, u; cin >> c >> v >> u;
		if (c == 'B') b.push_back({v, u});
		else r.push_back({v, u});
	}
	int rcnt = 0, bcnt = 0;
	for (auto [v, u]: r) {
		if (find(v) == find(u)) continue;
		Union(v, u);
		++rcnt;
	}
	for (int i = 1; i <= n; ++i) p[i] = i;
	for (auto [v, u]: b) {
		if (find(v) == find(u)) continue;
		Union(v, u);
		++bcnt;
	}
	rcnt = n - 1 - rcnt;
	// cout << rcnt << ' ' << bcnt << '\n';
	cout << (rcnt <= k && k <= bcnt) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> n >> m >> k;
		if (n == 0) break;
		solve();
	}
}