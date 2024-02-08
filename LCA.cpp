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
    for (auto [i, nd]: graph[v]) if (i != p) dfs(parents, dep, dis, graph, i, v, nd);
}

void getParents(vector<vector<int>>& parents, vector<int>& dep, int num, int& n) {
    for (int i = 1; i <= n; ++i) {
        if (parents[i][num - 1] == -1) parents[i][num] = -1;
        else parents[i][num] = parents[parents[i][num - 1]][num - 1];
    }
}

int LCA(vector<int>& dep, vector<vector<int>>& parents, int& h, int u, int v) {
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	int n; vector<vector<pair<int, LL>>> graph(n + 1);
	vector<int> dep(n + 1); vector<LL> dis(n + 1);
	int h = (int)ceil(log2(n));
	vector<vector<int>> parents(n + 1, vector<int>(h));
    dfs(parents, dep, dis, graph, 1, -1, 0LL);
	for (int i = 1; i < h; ++i) getParents(parents, dep, i, n);
}