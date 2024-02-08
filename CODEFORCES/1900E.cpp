#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n, m, id;
LL a[200001];
vector<int> graph[200001];
int d[200001];
int sccCnt;
int sccNum[200001];
bool finished[200001];
stack<int> S;
vector<vector<int>> SCC;
vector<int> ngraph[200001];
LL asum[200001];
int lcache[200001];
LL acache[200001];

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
		SCC.push_back(scc);
		++sccCnt;
	}
	return result;
}

pair<int, LL> matchCache(int v) {
	int& lret = lcache[v];
	LL& aret = acache[v];
	if (lret != -1) return make_pair(lret, aret);
	lret = SCC[v].size();
	aret = asum[v];
	for (auto i: ngraph[v]) {
		pair<int, LL> temp = matchCache(i);
		if (lret < temp.first + SCC[v].size()) {
			aret = asum[v] + temp.second;
			lret = temp.first + SCC[v].size();
		} else if (lret == temp.first + SCC[v].size()) {
			aret = min(aret, asum[v] + temp.second);
		}
	}
	return make_pair(lret, aret);
}

void solution() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int u, v;
	for (int i = 0; i <= n; ++i) {
		graph[i].clear();
		d[i] = 0;
		finished[i] = false;
		ngraph[i].clear();
		asum[i] = 0;
	}
	SCC.clear(); SCC.shrink_to_fit();
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		if (u != v) graph[u].push_back(v);
	}
	id = 1; sccCnt = 1; SCC.push_back({0});
	for (int i = 1; i <= n; ++i) if (d[i] == 0) DFS(i);
	for (int i = 1; i <= n; ++i) {
		for (auto j: graph[i]) if (sccNum[i] != sccNum[j]) ngraph[sccNum[i]].push_back(sccNum[j]);
		asum[sccNum[i]] += a[i];
	}
	for (int i = 1; i < sccCnt; ++i) ngraph[0].push_back(i);
	for (int i = 0; i < sccCnt; ++i) {
		lcache[i] = -1; acache[i] = -1;
	}
	pair<int, LL> ans = matchCache(0);
	cout << ans.first - 1 << " " << ans.second << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}

/*
1
14 22
2 3 5 7 3 4 1 4 3 4 2 2 5 1
1 2
2 3
2 4
3 1
4 4
4 5
5 6
5 6
5 12
6 7
6 8
7 5
7 7
7 9
8 4
9 11
10 9
11 10
11 10
12 13
13 14
14 12
*/