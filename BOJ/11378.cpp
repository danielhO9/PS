#include <bits/stdc++.h>
using namespace std;

bool bfs(int source, int sink, vector<int>& level, vector<int>& work, vector<vector<int>>& adj, vector<vector<int>>& capacity, vector<vector<int>>& flow) {
    for (auto& i: level) i = -1;
	level[source] = 0;
	queue<int> q;
	q.push(source);
	while (!q.empty()) {
        int here = q.front(); q.pop();
		for (auto there: adj[here]) {
			if (level[there] == -1 && capacity[here][there] - flow[here][there] > 0) {
				q.push(there);
                level[there] = level[here] + 1;
            }
        }
    }
	return level[sink] != -1;
}

int dfs(int here, int sink, int amount, vector<int>& level, vector<int>& work, vector<vector<int>>& adj, vector<vector<int>>& capacity, vector<vector<int>>& flow) {
    if (here == sink) return amount;
 	for (int& i = work[here]; i < adj[here].size(); ++i){
        int there = adj[here][i];
		if (level[there] == level[here] + 1 && capacity[here][there] - flow[here][there] > 0) {
            int ret = dfs(there, sink, min(capacity[here][there] - flow[here][there], amount), level, work, adj, capacity, flow);
			if (ret > 0) {
                flow[here][there] += ret;
                flow[there][here] -= ret;
				return ret;
            }
        }
    }
	return 0;
}

int networkFlow(int source, int sink, vector<vector<int>>& adj, vector<vector<int>>& capacity, vector<vector<int>>& flow) {
	const int MAX_V = adj.size();
	int totalFlow = 0;
	vector<int> level(MAX_V), work(MAX_V);
    while (bfs(source, sink, level, work, adj, capacity, flow)) {
        for (auto& i: work) i = 0;
		while (true) {
            int amount = dfs(source, sink, INT32_MAX, level, work, adj, capacity, flow);
            if (amount == 0) break;
            totalFlow += amount;
        }
    }
	return totalFlow;
}

void addEdge(int s, int e, int c, vector<vector<int>>& adj, vector<vector<int>>& capacity) {
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

