#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void dfs(vector<vector<int>>& parents, vector<int>& dep, vector<LL>& dis, vector<vector<pair<int, LL>>>& graph, int v, int p, LL d) {
    parents[v][0] = p;
    if (p == -1) {
        dep[v] = 1; dis[v] = 0LL;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [i, nd]: graph[v]) dfs(parents, dep, dis, graph, i, v, nd);
}

void getParents(vector<vector<int>>& parents, vector<int>& dep, int num, int& n) {
    for (int i = 1; i <= n; ++i) {
        if (parents[i][num - 1] == -1) parents[i][num] = -1;
        else parents[i][num] = parents[parents[i][num - 1]][num - 1];
    }
}

int LCA(vector<int>& dep, vector<vector<int>>& parents, int u, int v, int& h) {
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
    for (int i = 0; dif; ++i) {
        if (dif % 2) u = parents[u][i];
        dif /= 2;
    }
    if (u != v) {
        for (int i = h - 1; i >= 0; --i) {
            if (parents[u][i] != -1 && parents[u][i] != parents[v][i]) {
                u = parents[u][i]; v = parents[v][i];
            }
        }
        u = parents[u][0];
    }
    return u;
}

void solve() {
	int n; cin >> n;
	vector<vector<pair<int, LL>>> graph(n + 1);
	vector<bool> visited(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int A, B; cin >> A >> B;
		graph[A].push_back({B, 0LL});
		visited[B] = true;
	}
	vector<int> dep(n + 1); vector<LL> dis(n + 1);
	int h = (int)ceil(log2(n)); int root;
	for (int i = 1; i <= n; ++i) if (!visited[i]) {
		root = i; break;
	}
	vector<vector<int>> parents(n + 1, vector<int>(h));
    dfs(parents, dep, dis, graph, root, -1, 0LL);
	for (int i = 1; i < h; ++i) getParents(parents, dep, i, n);
	int A, B; cin >> A >> B;
	cout << LCA(dep, parents, A, B, h) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}