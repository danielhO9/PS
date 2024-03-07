#include <bits/stdc++.h>
using namespace std;

int sz[200001];

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void Union(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	if (x != y) sz[minn] = sz[x] + sz[y];
	parents[x] = minn; parents[y] = minn;
}

void solve() {
	int F; cin >> F;
	int cnt = 0; vector<int> parents(2 * F + 1);
	for (int i = 1; i <= 2 * F; ++i) {
		sz[i] = 1; parents[i] = i;
	}
	unordered_map<string, int> M;
	while (F--) {
		string s1, s2; cin >> s1 >> s2;
		if (M.find(s1) == M.end()) {
			M[s1] = ++cnt;
		}
		if (M.find(s2) == M.end()) {
			M[s2] = ++cnt;
		}
		Union(parents, M[s1], M[s2]);
		cout << sz[find(parents, M[s1])] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}