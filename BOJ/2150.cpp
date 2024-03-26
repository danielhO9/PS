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

void solve() {
	int V, E; cin >> V >> E;
	int MAX_V = V + 1;
	int src = 1;
	vector<vector<int>> adj(MAX_V);
	vector<vector<int>> scc;
	vector<int> sccNum(MAX_V, -1);
	for (int i = 0; i < E; ++i) {
		int A, B; cin >> A >> B;
		adj[A].push_back(B);
	}
	getSCC(src, adj, scc, sccNum);
	cout << scc.size() << '\n';
	sort(scc.begin(), scc.end());
	for (auto i: scc) {
		for (auto j: i) cout << j << ' ';
		cout << "-1\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}