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

int B, H, R, C;
int s[30][30];
bool sat[30][30];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

void solve() {
	cin >> B >> H >> R >> C;
	for (int i = 0; i < R; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < C; ++j) s[i][j] = tmp[j] - '0';
	}
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
		double tmp = 0.0;
		for (int k = 0; k < R; ++k) for (int l = 0; l < C; ++l) {
			tmp += (double) s[k][l] / ((k - i) * (k - i) + (l - j) * (l - j) + H * H);
		}
		sat[i][j] = (tmp >= B - 1e-6);
	}

	// for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) sat[i][j] = 1;
	// sat[2][2] = 0;
	// sat[2][4] = 0;

	int cnt = 0;
	for (auto i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			// cout << sat[i][j] << ' ';
			if (sat[i][j]) ++cnt;
		}
		// cout << '\n';
	}
	if (cnt == R * C) {
		cout << 0;
		return;
	}
	int MAX_V = R * C + 2;
	int source = R * C, sink = R * C + 1;
	vector<vector<Edge>> adj(MAX_V);
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
		for (int k = 0; k < 4; ++k) {
			int ni = i + dy[k], nj = j + dx[k];
			if (0 <= ni && ni < R && 0 <= nj && nj < C) {
				if (sat[i][j]) {
					if (sat[ni][nj]) addEdge(i * C + j, ni * C + nj, 43, adj);
				} else {
					if (sat[ni][nj]) addEdge(i * C + j, ni * C + nj, 11, adj);
				}
			}
		}
		if (!sat[i][j]) addEdge(source, i * C + j, 987654321, adj);
		if (i == 0 || j == 0 || i == R - 1 || j == C - 1) addEdge(i * C + j, sink, 987654321, adj);
	}
	auto ans = networkFlow(source, sink, adj);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}