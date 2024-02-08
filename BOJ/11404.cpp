#include <bits/stdc++.h>
using namespace std;

int n, m, dis[101][101];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (i != j) dis[i][j] = INT32_MAX;
	int a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		dis[a][b] = min(dis[a][b], c);
	}
	for (int b = 1; b <= n; ++b) for (int a = 1; a <= n; ++a) for (int c = 1; c <= n; ++c) {
		if (dis[a][b] != INT32_MAX && dis[b][c] != INT32_MAX) dis[a][c] = min(dis[a][c], dis[a][b] + dis[b][c]);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (dis[i][j] == INT32_MAX) cout << 0 << " ";
			else cout << dis[i][j] << " ";
		}
		cout << "\n";
	}
}