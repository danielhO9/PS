#include <bits/stdc++.h>
using namespace std;

int cache[100001];
vector<int> adj[100001];

int matchCache(int v, int p) {
	int& ret = cache[v];
	if (ret != -1) return ret;
	ret = 1;
	for (auto u: adj[v]) if (u != p) ret += matchCache(u, v);
	return ret;
}

void solve() {
	memset(cache, -1, sizeof(cache));
	int N, R, Q; cin >> N >> R >> Q;
	for (int i = 0; i < N - 1; ++i) {
		int U, V; cin >> U >> V;
		adj[U].push_back(V);
		adj[V].push_back(U);
	}
	matchCache(R, 0);
	for (int i = 0; i < Q; ++i) {
		int U; cin >> U;
		cout << cache[U] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}