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
	int n; vector<int> parent(n + 1);
	for (int i = 1; i <= n; ++i) parent[i] = i;
}