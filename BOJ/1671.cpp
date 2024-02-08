#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 50;

int n, m;
vector<int> adj[MAX_N];

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
		visited = vector<bool>(n, false);
		if (dfs(start)) ++size;
	}
	return size;
}

struct Shark {
	int s, v, i;
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n; m = n;
	vector<Shark> V;
	for (int j = 0; j < n; ++j) {
		int s, v, i; cin >> s >> v >> i;
		V.push_back({s, v, i});
	}
	for (int j = 0; j < n; ++j) {
		for (int k = 0; k < n; ++k) if (j != k) {
			if (V[j].i == V[k].i && V[j].s == V[k].s && V[j].v == V[k].v) {
				if (j > k) adj[j].push_back(k);
			} else if (V[j].i >= V[k].i && V[j].s >= V[k].s && V[j].v >= V[k].v) {
				adj[j].push_back(k);
			}
		}
	}
	cout << n - bipartiteMatch();
}