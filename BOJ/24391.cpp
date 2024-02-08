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

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, M; cin >> N >> M;
	vector<int> parents(N + 1);
	for (int i = 1; i <= N; ++i) parents[i] = i;
	int a, b;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		Union(parents, a, b);
	}
	int t = 0, ans = 0;
	for (int i = 0; i < N; ++i) {
		cin >> a;
		int b = find(parents, a);
		if (t != b) ++ans; 
		t = b;
	}
	cout << ans - 1;
}