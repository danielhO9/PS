#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> adj[3001];
bool visited[3001];
bool cycle[3001];

bool dfs(int v, int p, int src) {
	bool flag = false;
	visited[v] = true;
	for (auto u: adj[v]) if (u != p) {
		if (u == src) {
			flag = true;
		}
		else if (!visited[u]) flag |= dfs(u, v, src);
	}
	return flag;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 1; i <= N; ++i) {
		memset(visited, false, sizeof(visited));
		cycle[i] = dfs(i, -1, i);
	}
	for (int i = 1; i <= N; ++i) {
		memset(visited, 0, sizeof(visited));
		queue<pair<int, int>> Q; Q.push({i, 0});
		visited[i] = true;
		while (!Q.empty()) {
			auto here = Q.front(); Q.pop();
			if (cycle[here.first]) {
				cout << here.second << ' ';
				break;
			}
			for (auto there: adj[here.first]) if (!visited[there]) {
				Q.push({there, here.second + 1});
				visited[there] = true;
			} 
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}