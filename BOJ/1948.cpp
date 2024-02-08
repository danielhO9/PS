#include <bits/stdc++.h>
using namespace std;

void dfs(set<pair<int, int>>& S, vector<vector<int>>& parents, int v) {
	for (auto i: parents[v]) {
		if (S.find({i, v}) != S.end()) break;
		S.insert({i, v});
		dfs(S, parents, i);
	}
}

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<pair<int, int>>> graph(n + 1);
	vector<int> dim(n + 1, 0);
	vector<vector<int>> parents(n + 1);
	vector<int> dis(n + 1, 0);
	int a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		graph[a].push_back(make_pair(b, c));
		++dim[b];
	}
	int s, e; cin >> s >> e;
	deque<int> D; D.push_back(s);
	while (!D.empty()) {
		int here = D.front(); D.pop_front();
		for (auto [there, distance]: graph[here]) {
			if (dis[there] < distance + dis[here]) {
				dis[there] = distance + dis[here];
				parents[there].clear();
				parents[there].push_back(here);
			} else if (dis[there] == distance + dis[here]) {
				parents[there].push_back(here);
			}
			--dim[there];
			if (dim[there] == 0) {
				D.push_back(there);
			}
		}
	}
	cout << dis[e] << '\n';
	set<pair<int, int>> S;
	dfs(S, parents, e);
	cout << S.size();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}