#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> adj[2000];
vector<int> Q;
bool inQ[2000];
bool done;

void dfs(int v) {
	if (done) return;
	if (Q.size() == 5) {
		cout << 1; done = true;
		return;
	}
	for (auto u : adj[v]) if (!inQ[u]) {
		Q.push_back(u);
		inQ[u] = true;
		dfs(u);
		Q.pop_back();
		inQ[u] = false;
	}
}

void solve() {
	memset(inQ, false, sizeof(inQ));
	done = false;
	cin >> N >> M;
	while (M--) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 0; i < N; ++i) dfs(i);
	if (!done) cout << 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
}