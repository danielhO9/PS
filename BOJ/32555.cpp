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

int n, m;
char pw[101][100];
int ans[101][100];
int sig;

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < m; ++j) pw[i][j] = tmp[j];
	}
	cin >> sig;
	int rowy = 0;
	for (int i = 0; i < m; ++i) if (pw[0][i] == 'Y') ++rowy;
	++n;
	for (int i = 0; i < m; ++i) pw[n - 1][i] = 'G';
	vector<int> coly(m);
	vector<pair<int, int>> cols;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) coly[i] += (pw[j][i] == 'Y');
		cols.push_back({coly[i], i});
	}
	sort(cols.begin(), cols.end());
	for (int i = 0; i < rowy; ++i) {
		pw[n - 1][cols[i].second] = 'Y';
		++coly[cols[i].second];
	}
	for (int i = 0; i < m; ++i) if (coly[i] > rowy) {
		cout << "Bugged!";
		return;
	}

	int cur = 1;
	for (int t = 0; t < rowy; ++t) {
		int nrowy = rowy - t;
		int MAX_V = m + n + 4;
		int source = m + n, sink = m + n + 1;
		int sink1 = m + n + 2, sink2 = m + n + 3;
		vector<vector<Edge>> adj(MAX_V);
		int est = 0;
		for (int j = 0; j < m; ++j) {
			if (coly[j] == nrowy) {
				addEdge(j + n, sink1, 1, adj);
				++est;
			}
			else addEdge(j + n, sink2, 1, adj);
			for (int i = 0; i < n; ++i) if (pw[i][j] == 'Y') addEdge(i, j + n, 1, adj);
		}
		for (int i = 0; i < n; ++i) addEdge(source, i, 1, adj);
		addEdge(sink1, sink, est, adj);
		addEdge(sink2, sink, n - est, adj);
		auto flow = networkFlow(source, sink, adj);
		if (flow != n) {
			cout << "Bugged!";
			return;
		}

		for (int i = 0; i < n; ++i) {
			for (auto& edge: adj[i]) {
				if (edge.capacity == edge.flow) {
					pw[i][edge.vertex - n] = 'G';
					ans[i][edge.vertex - n] = cur;
					--coly[edge.vertex - n];
				}
			}
		}
		++cur;
	}
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (ans[i][j] == 0) ans[i][j] = cur++;

	if (cur - 1 > sig) {
		cout << "Bugged!"; return;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) cout << ans[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}