#include <bits/stdc++.h>
using namespace std;

int N, M;
bool adj[10001][1001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	while (M--) {
		int u, v; cin >> u >> v;
		adj[u][v] = true;
		adj[v][u] = true;
	}
	vector<int> v[2];
	for (int i = 2; i <= N; ++i) v[adj[1][i]].push_back(i);
	for (auto a: v[0]) for (auto b: v[0]) if (a != b) {
		if (!adj[a][b]) {
			cout << "NE";
			return 0;
		}
	}
	for (auto a: v[1]) for (auto b: v[1]) if (a != b) {
		if (!adj[a][b]) {
			cout << "NE";
			return 0;
		}
	}
	for (auto a: v[0]) for (auto b: v[1]) {
		if (adj[a][b]) {
			cout << "NE";
			return 0;
		}
	}
	cout << "DA";
}