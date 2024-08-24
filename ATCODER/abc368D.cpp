#include <bits/stdc++.h>
using namespace std;

int N, K;
vector<int> adj[200001];
vector<int> v;
bool used[200001];

void dfs(int v, int p) {
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		if (used[u]) used[v] = true;
	}
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N - 1; ++i) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 0; i < K; ++i) {
		int tmp; cin >> tmp;
		v.push_back(tmp);
		used[tmp] = true;
	}
	dfs(v[0], 0);
	int ans = 0;
	for (int i = 1; i <= N; ++i) if (used[i]) ++ans;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}