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

void getSCC(vector<vector<int>>& scc, vector<vector<int>>& adj, vector<int>& sccNum, int& V) {
	stack<int> S; vector<int> ord(V + 1, -1); int cnt = -1;
	// 시작점, 끝점 조절
	for (int i = 1; i <= V; ++i) if (ord[i] == -1) dfs(i, sccNum, adj, S, scc, ord, cnt);
}

void solve() {
	// V: max vertex num
	int V;
	vector<vector<int>> adj(V + 1);
	vector<vector<int>> scc;
	vector<int> sccNum(V + 1, -1);
	getSCC(scc, adj, sccNum, V);
}