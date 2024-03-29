#include <bits/stdc++.h>
using namespace std;

int dfs(int v, vector<int>& sccNum, vector<vector<int>>& adj, stack<int>& S, vector<vector<int>>& scc, vector<int>& ord, int& cnt) {
	ord[v] = ++cnt; S.push(v);
	int result = ord[v];
	for (int u: adj[v]) {
		if (ord[u] == -1) result = min(result, dfs(u, sccNum, adj, S, scc, ord, cnt));
		else if (sccNum[u] == -1) result = min(result, ord[u]);
	}
	if (result == ord[v]) {
		vector<int> temp;
		while (true) {
			int t = S.top(); S.pop();
			temp.push_back(t);
			sccNum[t] = scc.size();
			if (t == v) break;
		}
		sort(temp.begin(), temp.end());
		scc.push_back(temp);
	}
	return result;
}

void getSCC(int src, vector<vector<int>>& adj, vector<vector<int>>& scc, vector<int>& sccNum) {
	const int MAX_V = adj.size();
	stack<int> S; vector<int> ord(MAX_V, -1); int cnt = -1;
	for (int i = src; i < MAX_V; ++i) if (ord[i] == -1) dfs(i, sccNum, adj, S, scc, ord, cnt);
}

// time complexity: V+E
void solve() {
	int MAX_V;
	int src;
	vector<vector<int>> adj(MAX_V);
	vector<vector<int>> scc;
	vector<int> sccNum(MAX_V, -1);
	getSCC(src, adj, scc, sccNum);
}