#include <bits/stdc++.h>
using namespace std;

void dfs1(int v, vector<vector<int>>& graph, vector<int>& in, vector<int>& out, int p, int& cnt) {
	in[v] = ++cnt;
	for (int u: graph[v]) if (u != p) dfs1(u, graph, in, out, v, cnt);
	out[v] = cnt;
}

void solve() {
	int n, q; cin >> n >> q;
	vector<vector<int>> graph(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	vector<int> in(n + 1), out(n + 1); int cnt = 0;
	dfs1(1, graph, in, out, 0, cnt);
	

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}