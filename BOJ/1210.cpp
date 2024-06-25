#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
	int vertex;
	ll capacity;
	int reverse;
	ll flow = 0;
};

bool bfs(int source, int sink, vector<int>& level, vector<vector<Edge>>& adj) {
    for (auto& i: level) i = -1;
	level[source] = 0;
	queue<int> q;
	q.push(source);
	while (!q.empty()) {
        int here = q.front(); q.pop();
		for (Edge& edge: adj[here]) {
			int there = edge.vertex;
			if (level[there] == -1 && edge.capacity - edge.flow > 0) {
				q.push(there);
                level[there] = level[here] + 1;
            }
        }
    }
	return level[sink] != -1;
}

ll dfs(int here, int sink, ll amount, vector<int>& level, vector<int>& work, vector<vector<Edge>>& adj) {
    if (here == sink) return amount;
 	for (int& i = work[here]; i < adj[here].size(); ++i){
        Edge& edge = adj[here][i];
		int there = edge.vertex;
		if (level[there] == level[here] + 1 && edge.capacity - edge.flow > 0) {
            ll ret = dfs(there, sink, min(edge.capacity - edge.flow, amount), level, work, adj);
			if (ret > 0) {
                edge.flow += ret;
				adj[there][edge.reverse].flow -= ret;
				return ret;
            }
        }
    }
	return 0;
}

ll networkFlow(int source, int sink, vector<vector<Edge>>& adj) {
	const int MAX_V = adj.size();
	for (int i = 0; i < MAX_V; ++i) for (Edge& j: adj[i]) j.flow = 0;
	ll totalFlow = 0;
	vector<int> level(MAX_V), work(MAX_V);
    while (bfs(source, sink, level, adj)) {
        for (auto& i: work) i = 0;
		while (true) {
            ll amount = dfs(source, sink, INT32_MAX, level, work, adj);
            if (amount == 0) break;
            totalFlow += amount;
        }
    }
	return totalFlow;
}

void addEdge(int s, int e, ll c, vector<vector<Edge>>& adj) {
	adj[s].push_back({e, c, (int)adj[e].size()});
	adj[e].push_back({s, 0, (int)adj[s].size() - 1});
}

// time complexity: V^2*E
void solve() {
	int n, m; cin >> n >> m;
	int MAX_V = 2 * n;
	int source, sink; cin >> source >> sink;
	sink += n; --source; --sink;
	vector<vector<Edge>> adj(MAX_V);
	for (int i = 0; i < n; ++i) {
		ll c; cin >> c;
		addEdge(i, i + n, c, adj);
	}
	for (int i = 0; i < m; ++i) {
		int s, e; cin >> s >> e; --s; --e;
		addEdge(s + n, e, 987654321, adj);
		addEdge(e + n, s, 987654321, adj);
	}
	networkFlow(source, sink, adj);
	bool vis[2 * n]; memset(vis, 0, sizeof(vis));
	queue<int> q; q.push(source); vis[source] = true;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (Edge& edge: adj[here]) {
			if (edge.capacity > edge.flow && !vis[edge.vertex]) {
				vis[edge.vertex] = true;
				q.push(edge.vertex);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (vis[i] && !vis[i + n]) cout << i + 1 << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}