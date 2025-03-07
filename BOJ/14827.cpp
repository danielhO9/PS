#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int E, L, D;
};

int C;
vector<Edge> adj[15];
bool vis[15][2];

void solve() {
	cin >> C;
	for (int i = 0; i < C; ++i) adj[i].clear();
	for (int i = 0; i < 2 * C; ++i) {
		int E, L, D; cin >> E >> L >> D; --E;
		adj[i / 2].push_back({E, L, D});
	}
	int ans = INT32_MAX;
	for (int i = 0; i < (1 << C); ++i) {
		memset(vis, 0, sizeof(vis));
		int tm = 0, cur = 0, cnt = 0;
		while (true) {
			if (vis[cur][0] && vis[cur][1]) break;
			Edge edge;
			if (!vis[cur][(i >> cur) & 1]) {
				edge = adj[cur][(i >> cur) & 1];
				vis[cur][(i >> cur) & 1] = true;
			} else {
				edge = adj[cur][!((i >> cur) & 1)];
				vis[cur][!((i >> cur) & 1)] = true;
			}
			int dif = ((edge.L + 24) - (tm % 24)) % 24;
			tm += dif + edge.D;
			cur = edge.E;
			++cnt;
		}
		if (cnt == 2 * C) ans = min(ans, tm);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}