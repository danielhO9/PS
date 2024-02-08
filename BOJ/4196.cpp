#include <bits/stdc++.h>
using namespace std;

int N, M, id;
int d[100001];
int sccCnt;
int sccNum[100001];
vector<int> graph[100001];
bool finished[100001];
stack<int> S;
vector<vector<int>> SCC;
int deg[100001];

int DFS(int v) {
	d[v] = ++id;
	S.push(v);

	int result = d[v];
	for (int next : graph[v]) {
		if (d[next] == 0) result = min(result, DFS(next));
		else if (!finished[next]) result = min(result, d[next]);
	}

	if (result == d[v]) {
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
	int t; cin >> t;
	while (t--) {
		cin >> N >> M; int A, B;
		for (int i = 0; i < M; ++i) {
			cin >> A >> B;
			graph[A].push_back(B);
		}
		for (int i = 1; i <= N; ++i) if (d[i] == 0) DFS(i);
		for (int i = 1; i <= N; ++i) {
			for (auto j: graph[i]) {
				if (sccNum[i] != sccNum[j]) ++deg[sccNum[j]];
			}
		}
		int ans = 0;
		for (int i = 0; i < sccCnt; ++i) if (deg[i] == 0) ++ans;
		cout << ans << '\n';
		id = 0; sccCnt = 0;
		for (int i = 0; i <= N; ++i) {
			d[i] = 0; graph[i].clear(); graph[i].shrink_to_fit(); finished[i] = 0; deg[i] = 0;
			sccNum[i] = 0;
		}
		SCC.clear(); SCC.shrink_to_fit();
	}
}