#include <bits/stdc++.h>
using namespace std;

vector<int> aMatch, bMatch;
char pk[50][50];
map<pair<int, int>, int> M;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

bool dfs(int a, vector<bool>& visited, vector<vector<int>>& adj) {
	if (visited[a]) return false;
	visited[a] = true;
	for (auto b: adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b], visited, adj)) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatch(int MAX_N, int MAX_M, vector<vector<int>>& adj) {
	aMatch = vector<int>(MAX_N, -1);
	bMatch = vector<int>(MAX_M, -1);
	int size = 0;
	vector<bool> visited(MAX_N, false);
	for (int start = 0; start < MAX_N; ++start) {
		if (dfs(start, visited, adj)) {
			++size;
			for (int i = 0; i < MAX_N; ++i) visited[i] = false;
		}
	}
	return size;
}

vector<pair<int, int>> edge[100];
int MAX_N, MAX_M;

bool avail(int t) {
	vector<vector<int>> adj(MAX_N);
	int ans = bipartiteMatch(MAX_N, MAX_M, adj);
} 

// time complexity: V*E
void solve() {
	int R, C; cin >> R >> C;
	queue<pair<int, int>> Q;
	int cnum = 0, pnum = 0;
	for (int i = 0; i < R; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < C; ++j) {
			pk[i][j] = tmp[j];
			if (tmp[j] == 'C') {
				M[{i, j}] = ++cnum;
				Q.push({i, j});
			}
			if (tmp[j] == 'P') {
				M[{i, j}] = ++pnum;
			}
		}
	}
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}