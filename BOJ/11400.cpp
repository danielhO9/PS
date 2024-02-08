#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> ans;
int cnt = 0;

int dfs(int v, int p, vector<vector<int>>& graph, vector<int>& visited) {
	visited[v] = ++cnt;
	int ret = visited[v];
	for (int i = 0; i < graph[v].size(); ++i) {
		int u = graph[v][i];
		if (u == p) continue;
		if (!visited[u]) {
			int low = dfs(u, v, graph, visited);
			if (low > visited[v]) ans.push_back({min(v, u), max(v, u)});
			ret = min(ret, low);
		} else ret = min(ret, visited[u]);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int V, E; cin >> V >> E;
	vector<vector<int>> graph(V + 1);
	while (E--) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int> visited(V + 1);
	for (int i = 1; i <= V; ++i) if (!visited[i]) dfs(i, 0, graph, visited);
	cout << ans.size() << '\n';
	sort(ans.begin(), ans.end());
	for (auto i: ans) cout << i.first << ' ' << i.second << '\n';
}