#include <bits/stdc++.h>
using namespace std;

int n, m, r, t[101], dis[101][101], ans;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> r;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (i != j) dis[i][j] = INT32_MAX;
	for (int i = 1; i <= n; ++i) cin >> t[i];
	int a, b, l;
	for (int i = 0; i < r; ++i) {
		cin >> a >> b >> l;
		dis[a][b] = min(dis[a][b], l);
		dis[b][a] = min(dis[b][a], l);
	}
	for (int b = 1; b <= n; ++b) for (int a = 1; a <= n; ++a) for (int c = 1; c <= n; ++c) {
		if (dis[a][b] != INT32_MAX && dis[b][c] != INT32_MAX) dis[a][c] = min(dis[a][c], dis[a][b] + dis[b][c]);
	}
	for (int i = 1; i <= n; ++i) {
		int temp = 0;
		for (int j = 1; j <= n; ++j) {
			if (dis[i][j] <= m) temp += t[j];
		}
		ans = max(temp, ans);
	}
	cout << ans;
}