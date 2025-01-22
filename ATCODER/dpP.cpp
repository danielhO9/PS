#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int N;
vector<int> adj[100001];
ll cache[100001][2];

void dfs(int v, int p) {
	int cnt = 0;
	cache[v][0] = 1, cache[v][1] = 1;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
		cache[v][0] *= (cache[u][0] + cache[u][1]) % MOD;
		cache[v][0] %= MOD;
		cache[v][1] *= cache[u][0];
		cache[v][1] %= MOD;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1, 0);
	cout << (cache[1][0] + cache[1][1]) % MOD;
}