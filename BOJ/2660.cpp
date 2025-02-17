#include <bits/stdc++.h>
using namespace std;

int n;
int dis[51][51];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (i != j) dis[i][j] = 100;
	int u, v;
	while (true) {
		cin >> u >> v;
		if (u == -1) break;
		dis[u][v] = 1;
		dis[v][u] = 1;
	}
	for (int m = 1; m <= n; ++m) for (int s = 1; s <= n; ++s) for (int e = 1; e <= n; ++e) dis[s][e] = min(dis[s][e], dis[s][m] + dis[m][e]);
	vector<int> ans;
	int val = 100;
	for (int i = 1; i <= n; ++i) {
		int mx = 0;
		for (int j = 1; j <= n; ++j) if (i != j) {
			mx = max(mx, dis[i][j]);
		}
		if (val > mx) {
			ans = {i};
			val = mx;
		}
		else if (val == mx) ans.push_back(i);
	}
	cout << val << ' ' << ans.size() << '\n';
	for (auto i: ans) cout << i << ' ';
}