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

int n;
int score[30];
int idx[30];
int lim[30];

// time complexity: V^2*E
void solve() {
	cin >> n;
	memset(score, 0, sizeof(score));
	memset(lim, 0, sizeof(lim));
	vector<pair<int, int>> v;
	for (int i = 0; i < n; ++i) {
		string tmp; cin >> tmp;
		for (int j = i + 1; j < n; ++j) {
			if (tmp[j] == '1') score[i] += 2;
			else if (tmp[j] == '0') score[j] += 2;
			else if (tmp[j] == 'd') {
				++score[i];
				++score[j];
			} else {
				v.push_back({i, j});
				lim[i] += 2;
				lim[j] += 2;
			}
		}
	}
	int m = v.size();
	int MAX_V = n + m + 2;
	int source = n, sink = n + m + 1;
	vector<vector<Edge>> adj(MAX_V);
	for (int i = 0; i < m; ++i) {
		addEdge(n + i + 1, v[i].first, 2, adj);
		addEdge(n + i + 1, v[i].second, 2, adj);
		addEdge(source, n + i + 1, 2, adj);
	}
	for (int i = 0; i < n; ++i) {
		idx[i] = adj[i].size();
		addEdge(i, sink, 0, adj);
	}
	for (int i = 0; i < n; ++i) {
		int mxscore = score[i] + lim[i];
		bool flag = false;
		for (int j = 0; j < n; ++j) {
			adj[j][idx[j]].capacity = mxscore - score[j];
			if (mxscore - score[j] < 0) {
				flag = true;
				break;
			}
		}
		if (!flag && networkFlow(source, sink, adj) == m * 2) cout << i + 1 << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}