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
	// 시작점 조절
	for (int i = 0; i < V; ++i) if (ord[i] == -1) dfs(i, sccNum, adj, S, scc, ord, cnt);
}

void solve() {
	int N, M; cin >> N >> M;
	vector<vector<int>> adj(N + 1);
	for (int i = 0; i < M; ++i) {
		int A, B; cin >> A >> B;
		adj[A].push_back(B);
	}
	vector<vector<int>> scc;
	vector<int> sccNum(N + 1, -1);
	getSCC(scc, adj, sccNum, N);
	vector<int> deg(scc.size());
	vector<vector<int>> nadj(scc.size());
	for (int i = 0; i < N; ++i) {
		for (auto j: adj[i]) {
			if (sccNum[i] != sccNum[j]) {
				nadj[sccNum[i]].push_back(sccNum[j]);
				++deg[sccNum[j]];
			}
		}
	}
	vector<int> ans;
	for (int i = 0; i < scc.size(); ++i) {
		if (deg[i] == 0) {
			ans.push_back(i);
		}
	}
	if (ans.size() != 1) {
		cout << "Confused\n";
		cout << '\n';
		return;
	}
	for (auto i: scc[ans[0]]) {
		cout << i << '\n';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}