#include <bits/stdc++.h>
using namespace std;

int N, cache[1000001][2];
vector<int> graph[1000001];

int matchCache(int v, int p, int t) {
	int cnt = 0;
	for (auto i: graph[v]) if (i != p) ++cnt;
	if (cnt == 0) {
		if (t == 1) return 1;
		else return 0;
	}
	int& ret = cache[v][t];
	if (ret != -1) return ret;
	if (t == 1) {
		ret = 0;
		for (auto i: graph[v]) if (i != p) ret += min(matchCache(i, v, 0), matchCache(i, v, 1));
		++ret;
	} else {
		ret = 0;
		for (auto i: graph[v]) if (i != p) ret += matchCache(i, v, 1);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; int u, v;
	for (int i = 0; i < N - 1; ++i) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	memset(cache, -1, sizeof(cache));
	cout << min(matchCache(1, 0, 0), matchCache(1, 0, 1));
}