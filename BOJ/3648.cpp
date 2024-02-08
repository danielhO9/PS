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

void solve(int n, int m) {
	int V, E, idcnt; V = 2 * n;
	vector<int> id(V + 1);
	int sccCnt = 0;
	vector<int> sccNum(V + 1);
	vector<vector<int>> graph(V + 1);
	int a, b;
	while (m--) {
		cin >> a >> b;
		if (a < 0) a = abs(a) + n;
		if (b < 0) b = abs(b) + n;
		graph[a > n ? a - n : a + n].push_back(b);
		graph[b > n ? b - n : b + n].push_back(a);
	}
	graph[n + 1].push_back(1);
	vector<bool> finished(V + 1);
	stack<int> S;
	vector<vector<int>> SCC;
	for (int i = 1; i <= V; ++i) if (id[i] == 0) DFS(id, sccCnt, sccNum, graph, finished, S, SCC, idcnt, i);
	for (int i = 1; i <= n; ++i) if (sccNum[i] == sccNum[i + n]) {
		cout << "no" << '\n';
		return;
	}

	cout << "yes" << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	while (cin >> n >> m) solve(n, m);
}