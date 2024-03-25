#include <bits/stdc++.h>
using namespace std;

int networkFlow(int source, int sink, vector<vector<int>>& adj, vector<vector<int>>& capacity) {
	const int MAX_V = adj.size();
	int flow[MAX_V][MAX_V];
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (auto there: adj[here]) {
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1) break;
		int amount = INT32_MAX;
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

void addEdge(int s, int e, int c, vector<vector<int>>& adj, vector<vector<int>>& capacity) {
	adj[s].push_back(e);
	adj[e].push_back(s);
	capacity[s][e] = c;
}

void solve() {
	int N, P; cin >> N >> P;
	int MAX_V; MAX_V = N + 1;
	vector<vector<int>> adj(MAX_V);
	vector<vector<int>> capacity(MAX_V, vector<int>(MAX_V));
	for (int i = 0; i < P; ++i) {
		int s, e; cin >> s >> e;
		addEdge(s, e, 1, adj, capacity);
	}
	int source, sink; source = 1, sink = 2;
	auto ans = networkFlow(source, sink, adj, capacity);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}