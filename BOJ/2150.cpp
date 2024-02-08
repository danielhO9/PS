#include <bits/stdc++.h>
using namespace std;

int V, E, id;
int d[10001];
int sccCnt;
int sccNum[10001];
vector<int> graph[10001];
bool finished[10001];
stack<int> S;
vector<vector<int>> SCC;

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
	cin >> V >> E; int A, B;
	for (int i = 0; i < E; ++i) {
		cin >> A >> B;
		graph[A].push_back(B);
	}
	for (int i = 1; i <= V; i++) if (d[i] == 0) DFS(i);
	cout << sccCnt << '\n';
	sort(SCC.begin(), SCC.end());
	for (auto i: SCC) {
		for (auto j: i) cout << j << " ";
		cout << -1 << '\n';
	}
}

/*
5 6
1 2
1 3
2 4
3 4
4 5
5 2
*/