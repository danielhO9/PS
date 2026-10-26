#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> graph[200001];
int sz[200001];

void dfs(int v) {
	sz[v] = 1;
	for (auto i: graph[v]) {
		dfs(i);
		sz[v] += sz[i];
	}
}

int calc(int v, int k) {
	int tot = 0, mx = -1;
	for (int i: graph[v]) {
		tot += sz[i];
		if (mx == -1 || sz[mx] < sz[i]) mx = i;
	}
	if (tot == 0) return 0;
	if (sz[mx] - k <= tot - sz[mx]) return (tot - k) / 2;
	int add = tot - sz[mx];
	return add + calc(mx, max(0, k + add - 1));
}


void solution() {
	cin >> n; int p;
	for (int i = 1; i <= n; ++i) graph[i].clear();
	for (int i = 1; i <= n; ++i) sz[i] = 0;
	for (int i = 2; i <= n; ++i) {
		cin >> p;
		graph[p].push_back(i);
	}
	dfs(1);
	cout << calc(1, 0) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}