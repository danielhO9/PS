#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 10001;
vector<int> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
int cnt = 0;

void dfs(vector<int>& ret, int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
	bool flag = false;
	int child = 0;
    for (auto u: adj[v]) if (u != p) {
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
			++child;
            dfs(ret, u, v);
            if (low[u] >= ord[v]) flag = true;
			low[v] = min(low[u], low[v]);
        }
    }
	if (p == 0 && child > 1) ret.push_back(v); // root
	else if (p != 0 && flag) ret.push_back(v); // not root
}

// V: maximum vertex + 1
// TODO: 1-index
vector<int> getPoint(int V) {
	vector<int> ret;
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(ret, i, 0);
	return ret;
}