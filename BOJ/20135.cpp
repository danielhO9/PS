#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
	int vertex;
	ll capacity;
	int reverse;
	ll flow = 0;
};

const int MAX_V = 202;
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

// time complexity: V^2*E
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

int addEdge(int s, int e, ll c) {
    int ret = adj[s].size();
	adj[s].push_back({e, c, (int)adj[e].size()});
	adj[e].push_back({s, 0, (int)adj[s].size() - 1});
    return ret;
}

struct Query {
    int idx, u, v;
    ll s, e;
};

int N, M;
vector<Query> query;
ll p[201];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    int source = 0, sink = N + 1;
    for (int i = 1; i <= N; ++i) cin >> p[i];
    query.resize(M);
    for (int i = 0; i < M; ++i) {
        cin >> query[i].u >> query[i].v >> query[i].s >> query[i].e;
        query[i].idx = addEdge(query[i].u, query[i].v, query[i].e - query[i].s);
        p[query[i].u] -= query[i].s;
        p[query[i].v] += query[i].s;
    }
    ll sm = 0, tar = 0;
    for (int i = 1; i <= N; ++i) {
        if (p[i] > 0) {
            addEdge(source, i, p[i]);
            tar += p[i];
        } else addEdge(i, sink, -p[i]);
        sm += p[i];
    }
    if (sm != 0) {
        cout << -1;
        return 0;
    }
    ll flow = networkFlow(source, sink, N + 2);
    if (flow < tar) {
        cout << -1;
        return 0;
    }
    cout << 1 << '\n';
    for (int i = 0; i < M; ++i) {
        cout << adj[query[i].u][query[i].idx].flow + query[i].s << '\n';
    }
}