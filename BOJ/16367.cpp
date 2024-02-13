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
	int k, n; cin >> k >> n;
	int V, idcnt = 0;
	V = k * 2;
	vector<int> id(V + 1);
	int sccCnt = 0;
	vector<int> sccNum(V + 1);
	vector<vector<int>> graph(V + 1);
	vector<bool> finished(V + 1);
	stack<int> S;
	vector<vector<int>> SCC;
	while (n--) {
		vector<int> temp;
		for (int i = 0; i < 3; ++i) {
			int l; char c; cin >> l >> c;
			if (c == 'R') l += k;
			temp.push_back(l);
		}
		for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) if (i != j) {
			graph[temp[i] > k ? temp[i] - k : temp[i] + k].push_back(temp[j]);
		}
	}
	for (int i = 1; i <= V; ++i) if (id[i] == 0) DFS(id, sccCnt, sccNum, graph, finished, S, SCC, idcnt, i);
	for (int i = 1; i <= k; ++i) if (sccNum[i] == sccNum[i + k]) { cout << -1; return; }
	vector<int> ans(V + 1, -1);
	vector<vector<int>> ngraph(sccCnt); vector<int> deg(sccCnt);
	for (int i = 1; i <= V; ++i) for (int j: graph[i]) if (sccNum[i] != sccNum[j]) { ngraph[sccNum[i]].push_back(sccNum[j]); ++deg[sccNum[j]]; }
	deque<int> Q; for (int i = 0; i < sccCnt; ++i) if (deg[i] == 0) Q.push_back(i);
	while (!Q.empty()) {
		int here = Q.front(); Q.pop_front();
		for (auto i: SCC[here]) if (ans[i] == -1) { ans[i] = 0; ans[i > k ? i - k : i + k] = 1; }
		for (auto i: ngraph[here]) { --deg[i]; if (deg[i] == 0) Q.push_back(i); }
	}
	for (int i = 1; i <= k; ++i) {
		if (ans[i] == 1) cout << 'B';
		else cout << 'R';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
	return 0;
}