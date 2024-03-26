#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
	int vertex;
	ll capacity;
	int reverse;
	ll flow = 0;
};

int networkFlow(int source, int sink, vector<vector<Edge>>& adj) {
	const int MAX_V = adj.size();
	for (int i = 0; i < MAX_V; ++i) for (Edge& j: adj[i]) j.flow = 0;
	ll totalFlow = 0;
	int parent[MAX_V], ind[MAX_V];
	while (true) {
		memset(parent, -1, sizeof(parent));
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int i = 0; i < adj[here].size(); ++i) {
				Edge& edge = adj[here][i];
				int there = edge.vertex;
				if (edge.capacity - edge.flow > 0 && parent[there] == -1) {
					parent[there] = here;
					q.push(there);
					ind[there] = i;
				}
			}
		}
		if (parent[sink] == -1) break;

		ll amount = INT32_MAX;
		for (int p = sink; p != source; p = parent[p]) {
			Edge& edge = adj[parent[p]][ind[p]];
			amount = min(edge.capacity - edge.flow, amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			Edge& edge = adj[parent[p]][ind[p]];
			edge.flow += amount;
			adj[edge.vertex][edge.reverse].flow -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

void addEdge(int s, int e, ll c, vector<vector<Edge>>& adj) {
	adj[s].push_back({e, c, (int)adj[e].size()});
	adj[e].push_back({s, 0, (int)adj[s].size() - 1});
}

void solve() {
	int N, P; cin >> N >> P;
	int MAX_V; MAX_V = N + 1;
	vector<vector<Edge>> adj(MAX_V);
	for (int i = 0; i < P; ++i) {
		int s, e; cin >> s >> e;
		addEdge(s, e, 1, adj);
	}
	int source, sink; source = 1, sink = 2;
	auto ans = networkFlow(source, sink, adj);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}