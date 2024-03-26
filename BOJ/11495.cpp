#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};

struct Edge {
	int vertex;
	ll capacity;
	int reverse;
	ll flow = 0;
};

bool bfs(int source, int sink, vector<int>& level, vector<int>& work, vector<vector<Edge>>& adj) {
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

int dfs(int here, int sink, ll amount, vector<int>& level, vector<int>& work, vector<vector<Edge>>& adj) {
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
	for (int i = 0; i < MAX_V; ++i) for (Edge j: adj[i]) j.flow = 0;
	ll totalFlow = 0;
	vector<int> level(MAX_V), work(MAX_V);
    while (bfs(source, sink, level, work, adj)) {
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

// time complexity: V^2 * E
void solve() {
	int n, m; cin >> n >> m;
	int MAX_V = n * m + 2;
	int source = n * m, sink = n * m + 1;
	vector<vector<Edge>> adj(MAX_V);
	ll sum = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		if ((i + j) % 2 == 0) {
			ll cap; cin >> cap;
			addEdge(source, i * m + j, cap, adj);
			sum += cap;
			for (int k = 0; k < 4; ++k) {
				int ni = i + dy[k], nj = j + dx[k];
				if (0 <= ni && ni < n && 0 <= nj && nj < m) {
					addEdge(i * m + j, ni * m + nj, INT32_MAX, adj);
				}
			}
		} else {
			ll cap; cin >> cap;
			addEdge(i * m + j, sink, cap, adj);
			sum += cap;
		}
	}
	auto ans = networkFlow(source, sink, adj);
	cout << ans + (sum - 2 * ans) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}