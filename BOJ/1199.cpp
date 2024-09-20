#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int v;
	int cnt;
	int rev;
};

int N;
vector<Edge> adj[1001];
int last[1001];

void dfs(int v) {
	while (last[v] < adj[v].size()) {
		if (adj[v][last[v]].cnt == 0) {
			++last[v];
			continue;
		}
		--adj[v][last[v]].cnt;
		--adj[adj[v][last[v]].v][adj[v][last[v]].rev].cnt;
		dfs(adj[v][last[v]].v);
	}
	cout << v << ' ';
}

void solve() {
	cin >> N;
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
		int tmp; cin >> tmp;
		if (i >= j) continue;
		adj[i].push_back({j, tmp, (int) adj[j].size()});
		adj[j].push_back({i, tmp, (int) adj[i].size() - 1});
	}
	for (int i = 1; i <= N; ++i) {
		int cnt = 0;
		for (auto& j: adj[i]) cnt += j.cnt;
		if (cnt % 2) {
			cout << -1;
			return;
		}
	}
	dfs(1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}