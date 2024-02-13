#include <bits/stdc++.h>
using namespace std;

int DFS(vector<int>& id, int& sccCnt, vector<int>& sccNum, vector<vector<int>>& graph, vector<bool>& finished, stack<int>& S, vector<vector<int>>& SCC, int& idcnt, int v) {
	id[v] = ++idcnt;
	S.push(v);

	int result = id[v];
	for (int next : graph[v]) {
		if (id[next] == 0) result = min(result, DFS(id, sccCnt, sccNum, graph, finished, S, SCC, idcnt, next));
		else if (!finished[next]) result = min(result, id[next]);
	}

	if (result == id[v]) {
		vector<int> scc;
		while (1) {
			int t = S.top();
			S.pop();
			scc.push_back(t);
			finished[t] = true;
			sccNum[t] = sccCnt;
			if (t == v) break;
		}
		sort(scc.begin(), scc.end());
		SCC.push_back(scc);
		++sccCnt;
	}
	return result;
}

void solve() {
	int V, idcnt;
	vector<int> id(V + 1);
	int sccCnt = 0;
	vector<int> sccNum(V + 1);
	vector<vector<int>> graph(V + 1);
	vector<bool> finished(V + 1);
	stack<int> S;
	vector<vector<int>> SCC;
	for (int i = 1; i <= V; ++i) if (id[i] == 0) DFS(id, sccCnt, sccNum, graph, finished, S, SCC, idcnt, i);
}