#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj(501);
vector<int> aMatch, bMatch;
vector<bool> visited;

bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (auto b: adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b])) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatch() {
	aMatch = vector<int>(n, -1);
	bMatch = vector<int>(m, -1);
	int size = 0;
	for (int start = 0; start < n; ++start) {
		visited = vector<bool>(n, false);
		if (dfs(start)) ++size;
	}
	return size;
}

void solve() {
	int c, d, v; cin >> c >> d >> v;
	for (int i = 0; i < v; ++i) adj[i].clear();
	vector<pair<pair<int, int>, pair<int, int>>> cd(v);
	vector<int> l[2];
	n = v, m = v;
	for (int i = 0; i < v; ++i) {
		string s; cin >> s;
		int num = stoi(s.substr(1));
		if (s[0] == 'C') {
			cd[i].first = {0, num};
			l[0].push_back(i);
		}
		else {
			cd[i].first = {1, num};
			l[1].push_back(i);
		}
		cin >> s;
		num = stoi(s.substr(1));
		if (s[0] == 'C') cd[i].second = {0, num};
		else cd[i].second = {1, num};
	}
	for (auto i: l[0]) for (auto j: l[1]) {
		if (cd[i].first.second == cd[j].second.second || cd[i].second.second == cd[j].first.second) adj[i].push_back(j);
	}
	cout << v - bipartiteMatch() << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}