#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<pair<int, int>> graph[40001];
int dep[40001], parents[40001][17], dis[40001];

void dfs(int v, int p, int d) {
    parents[v][0] = p;
    if (p == -1) {
        dep[v] = 1; dis[v] = 0;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [i, nd]: graph[v]) if (i != p) dfs(i, v, nd);
}

void getParents(int num) {
    for (int i = 1; i <= N; ++i) {
        if (parents[i][num - 1] == -1) parents[i][num] = -1;
        else parents[i][num] = parents[parents[i][num - 1]][num - 1];
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
    for (int i = 0; dif; ++i) {
        if (dif % 2) u = parents[u][i];
        dif /= 2;
    }
    if (u != v) {
        for (int i = 16; i >= 0; --i) {
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
	cin >> N; int a, b, d;
	for (int i = 0; i < N - 1; ++i) {
		cin >> a >> b >> d;
		graph[a].push_back({b, d});
		graph[b].push_back({a, d});
	}
	dfs(1, -1, 0); for (int i = 1; i < 17; ++i) getParents(i);
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		cout << dis[a] + dis[b] - 2 * dis[LCA(a, b)] << '\n';
	}
}