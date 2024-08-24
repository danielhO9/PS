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

int R, C;
bool block[47][47];
int num[47][47][2];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

// time complexity: V^2*E
void solve() {
	cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < C; ++j) block[i][j] = (tmp[j] == 'X');
	}
	int cnt = 0;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) if (!block[i][j]) {
		if ((i + j) % 2 == 0) {
			num[i][j][0] = ++cnt;
			num[i][j][1] = ++cnt;
		}
		else num[i][j][0] = ++cnt;
	}
	int MAX_V = cnt + 2;
	int source = 0, sink = cnt + 1;
	vector<vector<Edge>> adj(MAX_V);
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
		if (!block[i][j] && i % 2 && !(j % 2)) {
			// cout << source << ' ' << num[i][j][0] << '\n';
			addEdge(source, num[i][j][0], 1, adj);
			for (int k = 0; k < 4; ++k) {
				int ny = i + dy[k], nx = j + dx[k];
				if (0 <= ny && ny < R && 0 <= nx && nx < C && !block[ny][nx]) addEdge(num[i][j][0], num[ny][nx][0], 1, adj);
			}
		} else if (!block[i][j] && !(i % 2) && j % 2) {
			// cout << num[i][j][0] << ' ' << sink << '\n';
			addEdge(num[i][j][0], sink, 1, adj);
			for (int k = 0; k < 4; ++k) {
				int ny = i + dy[k], nx = j + dx[k];
				if (0 <= ny && ny < R && 0 <= nx && nx < C && !block[ny][nx]) addEdge(num[ny][nx][1], num[i][j][0], 1, adj);
			}
		} else if (!block[i][j] && (i + j) % 2 == 0) {
			addEdge(num[i][j][0], num[i][j][1], 1, adj);
		}
	}
	auto ans = networkFlow(source, sink, adj);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}