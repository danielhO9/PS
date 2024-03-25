#include <bits/stdc++.h>
using namespace std;

int N;

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

bool isAvailable(int c, int source, int sink, int sum, vector<vector<int>>& adj, vector<vector<int>>& capacity, vector<vector<int>>& flow) {
	const int MAX_V = adj.size();
	for (int i = 0; i < MAX_V; ++i) for (int j = 0; j < MAX_V; ++j) flow[i][j] = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int num = i * N + j + N * 2;
			capacity[i][num] = c;
		}
	}
	int amount = networkFlow(source, sink, adj, capacity, flow);
	if (amount == sum) return true;
	else return false;
}

void solve() {
	cin >> N;
	// source: 2 * N + N ^ 2, 행 합 : 0 ~ N - 1, 열 합: N ~ N * 2 - 1, num: N * 2 + (0 ~ N ^ 2 - 1), sink: 2 * N + N ^ 2 + 1
	int MAX_V = N * 2 + N * N + 2;
	int source = 2 * N + N * N, sink = 2 * N + N * N + 1;
	vector<vector<int>> adj(MAX_V);
	vector<vector<int>> capacity(MAX_V, vector<int>(MAX_V));
	vector<vector<int>> flow(MAX_V, vector<int>(MAX_V, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int num = i * N + j + N * 2;
			addEdge(i, num, 0, adj, capacity);
		}
		addEdge(source, i, 0, adj, capacity);
		cin >> capacity[source][i];
	}
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int num = j * N + i + N * 2;
			addEdge(num, i + N, INT32_MAX, adj, capacity);
		}
		addEdge(i + N, sink, 0, adj, capacity);
		cin >> capacity[i + N][sink];
		sum += capacity[i + N][sink];
	}
	int l = 0, r = 10000, mid;
	while (l < r) {
		mid = (l + r) / 2;
		if (isAvailable(mid, source, sink, sum, adj, capacity, flow)) r = mid;
		else l = mid + 1;
	}
	cout << l << '\n'; isAvailable(l, source, sink, sum, adj, capacity, flow);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int num = i * N + j + 2 * N;
			cout << flow[i][num] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}