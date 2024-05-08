#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> adj[100001];
int dep[100001];
int par[100001];

void solve() {
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	memset(dep, -1, sizeof(dep));
	queue<int> Q; dep[1] = 0; Q.push(1); par[1] = 0;
	while (!Q.empty()) {
		auto here = Q.front(); Q.pop();
		for (auto there: adj[here]) if (dep[there] == -1) {
			dep[there] = dep[here] + 1; par[there] = here;
			Q.push(there);
		}
	}
	vector<int> V(N);
	for (int i = 0; i < N; ++i) {
		cin >> V[i];
	}
	if (V[0] != 1) {
		cout << 0; return;
	}
	int idx = 0;
	for (int i = 1; i < N; ++i) {
		while (par[V[i]] != V[idx]) {
			++idx;
			if (idx == i) {
				cout << 0;
				return;
			}
		}
	}
	cout << 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}