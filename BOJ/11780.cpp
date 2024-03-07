#include <bits/stdc++.h>
using namespace std;

vector<int> way[101][101];
int mid[101][101];

void getAns(int s, int e) {
	if (!way[s][e].empty()) return;
	int m = mid[s][e];
	if (m == s || m == e) {
		way[s][e].push_back(s);
		way[s][e].push_back(e);
		return;
	}
	getAns(s, m); getAns(m, e);
	for (auto i: way[s][m]) way[s][e].push_back(i);
	way[s][e].pop_back();
	for (auto i: way[m][e]) way[s][e].push_back(i);
	return;
}

void solve() {
	int n, m; cin >> n >> m;
	int dis[n + 1][n + 1]; for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) dis[i][j] = 987654321;
	for (int i = 1; i <= n; ++i) dis[i][i] = 0;
	for (int i = 0; i < m; ++i) {
		int a, b, c; cin >> a >> b >> c;
		if (dis[a][b] > c) {
			mid[a][b] = a;
			dis[a][b] = c;
		}
	}
	for (int m = 1; m <= n; ++m) for (int s = 1; s <= n; ++s) for (int e = 1; e <= n; ++e) {
		if (dis[s][e] > dis[s][m] + dis[m][e]) {
			dis[s][e] = dis[s][m] + dis[m][e];
			mid[s][e] = m;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (dis[i][j] != 987654321) cout << dis[i][j] << ' ';
			else cout << 0 << ' ';
		}
		cout << '\n';
	}
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
		if (dis[i][j] == 0 || dis[i][j] == 987654321) {
			cout << 0 << '\n';
			continue;
		}
		getAns(i, j);
		cout << way[i][j].size() << ' ';
		for (auto k: way[i][j]) cout << k << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}