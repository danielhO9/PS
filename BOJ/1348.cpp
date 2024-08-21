#include <bits/stdc++.h>
using namespace std;

vector<int> aMatch, bMatch;
char pk[50][50];
unordered_map<int, int> M;
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

vector<pair<int, int>> edge[2500];
int MAX_N, MAX_M;
int dis[50][50];

bool avail(int t) {
	vector<vector<int>> adj(MAX_N);
	for (int i = 0; i <= t; ++i) {
		for (auto j: edge[i]) {
			adj[j.first].push_back(j.second);
		}
	}
	int ans = bipartiteMatch(MAX_N, MAX_M, adj);
	return ans == MAX_N;
} 

// time complexity: V*E
void solve() {
	int R, C; cin >> R >> C;
	int cnum = 0, pnum = 0;
	for (int i = 0; i < R; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < C; ++j) {
			pk[i][j] = tmp[j];
			if (tmp[j] == 'C') M[i * 50 + j] = cnum++;
			if (tmp[j] == 'P') M[i * 50 + j] = pnum++;
		}
	}
	if (cnum == 0) {
		cout << 0;return;
	}
	MAX_N = cnum; MAX_M = pnum;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) if (pk[i][j] == 'C') {
		memset(dis, -1, sizeof(dis));
		queue<pair<int, int>> Q; Q.push({i, j});
		dis[i][j] = 0;
		while (!Q.empty()) {
			auto here = Q.front(); Q.pop();
			int y = here.first, x = here.second;
			for (int k = 0; k < 4; ++k) {
				int ny = y + dy[k], nx = x + dx[k];
				if (0 <= ny && ny < R && 0 <= nx && nx < C && pk[ny][nx] != 'X' && dis[ny][nx] == -1) {
					dis[ny][nx] = dis[y][x] + 1;
					Q.push({ny, nx});
					if (pk[ny][nx] == 'P') {
						edge[dis[ny][nx]].push_back({M[50 * i + j], M[50 * ny + nx]});
					}
				}
			}
		}
	}
	if (!avail(2499)) {
		cout << -1;
		return;
	}
	int l = 0, r = 2499;
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (avail(mid)) r = mid;
		else l = mid;
	}
	cout << r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}