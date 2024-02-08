#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>>& graph, vector<int>& dep, int v, int p) {
	dep[v] = dep[p] + 1;
	for (auto i: graph[v]) if (dep[i] == -1) dfs(graph, dep, i, v);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	int a, b; cin >> a >> b;
	int m; cin >> m;
	vector<vector<int>> graph(n + 1);
	int x, y;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	vector<int> dep(n + 1, -1);
	dfs(graph, dep, a, 0);
	cout << dep[b];
}