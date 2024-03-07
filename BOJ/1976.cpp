#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void Union(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	parents[x] = minn; parents[y] = minn;
}

void solve() {
	int N, M; cin >> N >> M;
	vector<int> parents(N + 1);
	for (int i = 1; i <= N; ++i) parents[i] = i;
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
		int t; cin >> t;
		if (t == 1) Union(parents, i, j);
	}
	vector<int> li(M); for (int i = 0; i < M; ++i) cin >> li[i];
	for (int i = 0; i < M - 1; ++i) {
		if (find(parents, li[i]) != find(parents, li[i + 1])) {
			cout << "NO"; return;
		}
	}
	cout << "YES";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}