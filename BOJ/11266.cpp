#include <bits/stdc++.h>
using namespace std;

int dfs(int v, bool isRoot, vector<vector<int>>& graph, int& cnt, vector<int>& visited, vector<bool>& articulation) {
	visited[v] = ++cnt;
	int ret = visited[v];
	int child = 0;
	for (int i = 0; i < graph[v].size(); ++i) {
		int u = graph[v][i];
		if (!visited[u]) {
			++child;
			int low = dfs(u, false, graph, cnt, visited, articulation);
			if (!isRoot && low >= visited[v]) articulation[v] = true;
			ret = min(ret, low);
		} else ret = min(ret, visited[u]);
	}
	if (isRoot) articulation[v] = (child >= 2);
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
	vector<int> visited(V + 1); int cnt = 0;
	vector<bool> articulation(V + 1);
	for (int i = 1; i <= V; ++i) if (!visited[i]) dfs(i, true, graph, cnt, visited, articulation);
	int ans = 0; for (auto i: articulation) if (i) ++ans; cout << ans << '\n';
	for (int i = 1; i <= V; ++i) if (articulation[i]) cout << i << ' ';
}