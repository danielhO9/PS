#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 100001;
vector<int> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
bool vis[MAX_V];
int cnt = 0, col = 0;
vector<int> bcc[MAX_V];

void dfs(int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    for (auto u: adj[v]) if (u != p) {
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
            dfs(u, v);
			low[v] = min(low[u], low[v]);
        }
    }
}

void color(int v, int c, int p) {
    if (c > 0) bcc[v].push_back(c);
    vis[v] = true;
    for (auto u: adj[v]) if (u != p) {
        if (vis[u]) continue;
        if (low[u] >= ord[v]) {
            bcc[v].push_back(++col);
            color(u, col, v);
        } else color(u, c, v);
    }
}

// V: maximum vertex + 1
// 1-index
void getBcc(int V) {
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(i, 0);
    for (int i = 1; i < V; ++i) if (!vis[i]) color(i, 0, 0);
}