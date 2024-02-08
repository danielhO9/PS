#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

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

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int V, E, idcnt; cin >> V >> E;
	vector<int> id(V + 1);
	int sccCnt;
	vector<int> sccNum(V + 1);
	vector<vector<int>> graph(V + 1);
	vector<bool> finished(V + 1);
	stack<int> S;
	vector<vector<int>> SCC;
	while (E--) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
	}
	for (int i = 1; i <= V; ++i) if (id[i] == 0) DFS(id, sccCnt, sccNum, graph, finished, S, SCC, idcnt, i);
	vector<vector<int>> ngraph(sccCnt);
	vector<int> deg(sccCnt);
	for (int i = 1; i <= V; ++i) for (auto j: graph[i]) {
		if (sccNum[i] != sccNum[j]) {
			ngraph[sccNum[i]].push_back(sccNum[j]);
			++deg[sccNum[j]];
		}
	}
	vector<LL> money(sccCnt), ans(sccCnt);
	for (int i = 1; i <= V; ++i) {
		LL m; cin >> m;
		money[sccNum[i]] += m;
	}
	vector<int> zero;
	for (int i = 0; i < sccCnt; ++i) if (deg[i] == 0) zero.push_back(i);
	int Sv, P; cin >> Sv >> P;
	vector<int> p; while (P--) { int x; cin >> x; p.push_back(sccNum[x]); }
	ans[sccNum[Sv]] = money[sccNum[Sv]];
	while (!zero.empty()) {
		int v = zero.back(); zero.pop_back();
		for (auto i: ngraph[v]) {
			if (ans[v] != 0) ans[i] = max(ans[i], ans[v] + money[i]);
			--deg[i]; if (deg[i] == 0) zero.push_back(i);
		}

	}
	LL ret = 0;
	for (auto i: p) ret = max(ret, ans[i]);
	cout << ret;
}