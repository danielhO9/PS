#include <bits/stdc++.h>
using namespace std;

int networkFlow(int source, int sink, vector<vector<int> >& adj, vector<vector<int> >& capacity, vector<vector<int>>& flow) {
	const int MAX_V = adj.size();
	int totalFlow = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there: adj[here]) {
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

void addEdge(int s, int e, int c, vector<vector<int> >& adj, vector<vector<int> >& capacity) {
	adj[s].push_back(e);
	adj[e].push_back(s);
	capacity[s][e] = c;
}

void solve() {
	int N, M, K; cin >> N >> M >> K;
	// source: 0, 직원: N, 일: 1000 + M, 벌점: 2001, sink: 2002
	int source, sink; source = 0, sink = N + M + 2;
	int MAX_V; MAX_V = 2003;
	vector<vector<int> > adj(MAX_V);
	vector<vector<int> > capacity(MAX_V, vector<int>(MAX_V));
	vector<vector<int>> flow(MAX_V, vector<int>(MAX_V, 0));
	addEdge(source, N + M + 1, K, adj, capacity);
	for (int i = 1; i <= N; ++i) {
		addEdge(source, i, 1, adj, capacity);
		addEdge(N + M + 1, i, 2000, adj, capacity);
		int cnt; cin >> cnt;
		for (int j = 0; j < cnt; ++j) {
			int w; cin >> w;
			addEdge(i, N + w, 1, adj, capacity);
		}
	}
	for (int i = 1; i <= M; ++i) {
		addEdge(N + i, sink, 1, adj, capacity);
	}
	int ans = networkFlow(source, sink, adj, capacity, flow);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

