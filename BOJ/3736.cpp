#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
	int vertex;
	ll capacity;
	int reverse;
	ll flow = 0;
};

const int MAX_V = 20002;
vector<Edge> adj[MAX_V];

bool bfs(int source, int sink, vector<int>& level) {
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

ll dfs(int here, int sink, ll amount, vector<int>& level, vector<int>& work) {
    if (here == sink) return amount;
 	for (int& i = work[here]; i < adj[here].size(); ++i){
        Edge& edge = adj[here][i];
		int there = edge.vertex;
		if (level[there] == level[here] + 1 && edge.capacity - edge.flow > 0) {
            ll ret = dfs(there, sink, min(edge.capacity - edge.flow, amount), level, work);
			if (ret > 0) {
                edge.flow += ret;
				adj[there][edge.reverse].flow -= ret;
				return ret;
            }
        }
    }
	return 0;
}

// V: maximum vertex + 1
ll networkFlow(int source, int sink, int V) {
	for (int i = 0; i < V; ++i) for (Edge& j: adj[i]) j.flow = 0;
	ll totalFlow = 0;
	vector<int> level(V), work(V);
    while (bfs(source, sink, level)) {
        for (auto& i: work) i = 0;
		while (true) {
            ll amount = dfs(source, sink, INT32_MAX, level, work);
            if (amount == 0) break;
            totalFlow += amount;
        }
    }
	return totalFlow;
}

void addEdge(int s, int e, ll c) {
	adj[s].push_back({e, c, (int)adj[e].size()});
	adj[e].push_back({s, 0, (int)adj[s].size() - 1});
}

int n;

void solve() {
    for (int i = 0; i <= 2 * n + 1; ++i) adj[i].clear();
    int src = 2 * n, sink = 2 * n + 1;
    for (int i = 0; i < n; ++i) {
        string tmp; cin >> tmp; tmp.pop_back();
        int job = stoi(tmp);
        assert(0 <= job && job < n);
        cin >> tmp; int cnt = stoi(tmp.substr(1, (int)tmp.size() - 2));
        for (int j = 0; j < cnt; ++j) {
            int s; cin >> s;
            assert(n <= s && s < 2 * n);
            addEdge(job, s, 1);
        }
    }
    for (int i = 0; i < n; ++i) addEdge(src, i, 1);
    for (int i = n; i < 2 * n; ++i) addEdge(i, sink, 1);
    cout << networkFlow(src, sink, 2 * n + 2) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (cin >> n) solve();
}