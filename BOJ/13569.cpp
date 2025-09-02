#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e12;

struct Edge {
	int vertex;
	ll capacity;
	int reverse;
	ll flow = 0;
};

const int MAX_V = 90000;
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

pair<int, int> read(double s) {
    s += 0.01;
    int l, r;
    l = s;
    if ((double) l + 0.05 < s) r = l + 1;
    else r = l;

    return make_pair(l, r);
}

int N, M, idx[200][200], idxrow[200], idxcol[200], verrow[200], vercol[200];
pair<int, int> lr[200][200], rowsm[200], colsm[200];
vector<int> demand;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            double s; cin >> s;
            lr[i][j] = read(s);
        }
        double s; cin >> s;
        rowsm[i] = read(s);
    }
    for (int i = 0; i < M; ++i) {
        double s; cin >> s;
        colsm[i] = read(s);
    }
    demand.resize(N * M * 2 + N + M + 4);

    int num = N * M * 2;
    int source = num++;
    int sink = num++;

    int a = num++;
    int b = num++;
    addEdge(b, a, INF);
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
        idx[i][j] = addEdge(i * M + j, i * M + j + N * M, lr[i][j].second - lr[i][j].first);
        demand[i * M + j + N * M] += lr[i][j].first;
        demand[i * M + j] -= lr[i][j].first;
    }
    for (int i = 0; i < N; ++i) {
        verrow[i] = num++;
        idxrow[i] = addEdge(a, verrow[i], rowsm[i].second - rowsm[i].first);
        demand[verrow[i]] += rowsm[i].first;
        demand[a] -= rowsm[i].first;
        for (int j = 0; j < M; ++j) addEdge(verrow[i], i * M + j, INF);
    }
    for (int j = 0; j < M; ++j) {
        vercol[j] = num++;
        idxcol[j] = addEdge(vercol[j], b, colsm[j].second - colsm[j].first);
        demand[b] += colsm[j].first;
        demand[vercol[j]] -= colsm[j].first;
        for (int i = 0; i < N; ++i) addEdge(i * M + j + N * M, vercol[j], INF);
    }
    for (int i = 0; i < demand.size(); ++i) {
        if (demand[i] > 0) addEdge(source, i, demand[i]);
        else if (demand[i] < 0) addEdge(i, sink, -demand[i]);
    }

    networkFlow(source, sink, ++num);
    for (int i = 0; i < N; ++i) {
        ll sm = 0;
        for (int j = 0; j < M; ++j) {
            cout << lr[i][j].first + adj[i * M + j][idx[i][j]].flow << ' ';
            sm += lr[i][j].first + adj[i * M + j][idx[i][j]].flow;
        }
        cout << rowsm[i].first + adj[a][idxrow[i]].flow << '\n';
    }
    for (int i = 0; i < M; ++i) {
        ll sm = 0;
        for (int j = 0; j < N; ++j) sm += lr[j][i].first + adj[j * M + i][idx[j][i]].flow;
        cout << colsm[i].first + adj[vercol[i]][idxcol[i]].flow << ' ';
    }
}