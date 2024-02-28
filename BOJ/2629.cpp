#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> weight(n + 1); for (int i = 1; i <= n; ++i) cin >> weight[i];
	int q; cin >> q;
	vector<int> marble(q); for (int i = 0; i < q; ++i) cin >> marble[i];
	bool vis[30001][n + 1];
	memset(vis, 0, sizeof(vis));
	vis[15000][0] = true;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= 30000; ++j) {
			if (vis[j][i - 1]) {
				vis[j + weight[i]][i] = true;
				vis[j][i] = true;
				vis[j - weight[i]][i] = true;
			}
		}
	}
	for (auto i: marble) {
		if (i + 15000 <= 30000 && vis[i + 15000][n]) cout << "Y ";
		else cout << "N ";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}