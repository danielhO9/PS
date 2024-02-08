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
	int N, M; cin >> N >> M;
	int V, E, idcnt;
	V = 2 * N;
	vector<int> id(V + 1);
	int sccCnt = 0;
	vector<int> sccNum(V + 1);
	vector<vector<int>> graph(V + 1);
	while (M--) {
		int i, j; cin >> i >> j;
		if (i < 0) i = abs(i) + N;
		if (j < 0) j = abs(j) + N;
		graph[i > N ? i - N : i + N].push_back(j);
		graph[j > N ? j - N : j + N].push_back(i);
	}
	vector<bool> finished(V + 1);
	stack<int> S;
	vector<vector<int>> SCC;
	for (int i = 1; i <= V; ++i) if (id[i] == 0) DFS(id, sccCnt, sccNum, graph, finished, S, SCC, idcnt, i);
	for (int i = 1; i <= N; ++i) {
		if (sccNum[i] == sccNum[i + N]) {
			cout << 0;
			return;
		}
	}
	cout << 1 << '\n';
	vector<int> degree(V + 1), ans(V + 1, -1);
	vector<vector<int>> ngraph(sccCnt);
	for (int i = 1; i <= V; ++i) for (int j: graph[i]) {
		if (sccNum[i] != sccNum[j]) {
			ngraph[sccNum[i]].push_back(sccNum[j]);
			++degree[sccNum[j]];
		}
	}
	deque<int> D;
	for (int i = 0; i < sccCnt; ++i) if (degree[i] == 0) D.push_back(i);
	while (!D.empty()) {
		int v = D.front(); D.pop_front();
		for (auto i: SCC[v]) if (ans[i] == -1) {
			ans[i] = 0; ans[i > N ? i - N : i + N] = 1;
		}
		for (auto i: ngraph[v]) {
			--degree[i];
			if (degree[i] == 0) D.push_back(i);
		} 
	}
	for (int i = 1; i <= N; ++i) cout << ans[i] << ' ';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}