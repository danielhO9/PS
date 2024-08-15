#include <bits/stdc++.h>
using namespace std;

int N, M, L;
vector<pair<int, int>> adj[100000];
bool vis[100000];
int dis[2][100000];
int ans = 0;
vector<int> radius;

void dfs(int t, int v, int p) {
	for (auto [u, c]: adj[v]) if (u != p) {
		dis[t][u] = dis[t][v] + c;
		dfs(t, u, v);
	}
}

void tree(int v) {
	if (vis[v]) return;
	vis[v] = true;
	vector<int> vertex; vertex.push_back(v);
	queue<int> q; q.push(v);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (auto [u, _]: adj[here]) if (!vis[u]) {
			vertex.push_back(u);
			q.push(u);
			vis[u] = true;
		}
	}

	dis[0][v] = 0; dfs(0, v, -1);
	int maxdis = -1; v = -1;
	for (auto i: vertex) {
		if (maxdis < dis[0][i]) {
			v = i;
			maxdis = dis[0][i];
		}
	}

	dis[0][v] = 0; dfs(0, v, -1);
	maxdis = -1;
	int u = -1;
	for (auto i: vertex) {
		if (maxdis < dis[0][i]) {
			u = i;
			maxdis = dis[0][i];
		}
	}
	ans = max(ans, maxdis);
	dis[1][u] = 0; dfs(1, u, -1);
	int rad = INT32_MAX;
	for (auto i: vertex) {
		rad = min(rad, max(dis[0][i], dis[1][i]));
	}
	radius.push_back(rad);
}

void solve() {
	cin >> N >> M >> L;
	for (int i = 0; i < M; ++i) {
		int a, b, t; cin >> a >> b >> t;
		adj[a].push_back({b, t});
		adj[b].push_back({a, t});
	}
	for (int i = 0; i < N; ++i) tree(i);
	sort(radius.begin(), radius.end());
	int lidx = radius.size(); --lidx;
	if (radius.size() >= 2) {
		ans = max(ans, radius[lidx] + radius[lidx - 1] + L);
	}
	if (radius.size() >= 3) {
		ans = max(ans, radius[lidx - 1] + radius[lidx - 2] + 2 * L);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}