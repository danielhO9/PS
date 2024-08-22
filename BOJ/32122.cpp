#include <bits/stdc++.h>
using namespace std;

vector<int> aMatch, bMatch;

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
	int size = 0;
	vector<bool> visited(MAX_N, false);
	for (int start = 0; start < MAX_N; ++start) if (aMatch[start] == -1) {
		if (dfs(start, visited, adj)) {
			++size;
			for (int i = 0; i < MAX_N; ++i) visited[i] = false;
		}
	}
	return size;
}

int a[100][100];
pair<int, int> cor[10001];
bool pos[100][100];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int val[100][100];
int ans[10001];

// time complexity: V*E
void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> a[i][j];
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cor[a[i][j]] = {i, j};
    
	int MAX_N = N * N / 2, MAX_M = N * N / 2;
    int ncnt = 0, mcnt = 0;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
        if ((i + j) % 2) val[i][j] = ncnt++;
        else val[i][j] = mcnt++;
    }
	vector<vector<int>> adj(MAX_N);
    aMatch = vector<int>(MAX_N, -1);
	bMatch = vector<int>(MAX_M, -1);
    for (int i = 1; i <= N * N; ++i) {
        pos[cor[i].first][cor[i].second] = true;
        int y = cor[i].first, x = cor[i].second;
        for (int k = 0; k < 4; ++k) {
            int ny = y + dy[k], nx = x + dx[k];
            if (0 <= ny && ny < N && 0 <= nx && nx < N && pos[ny][nx]) {
                if ((y + x) % 2) adj[val[y][x]].push_back(val[ny][nx]);
                else adj[val[ny][nx]].push_back(val[y][x]);
            }
        }
        ans[i] = bipartiteMatch(MAX_N, MAX_M, adj);
    }
    // for (int i = 1; i <= N * N; ++i) cout << ans[i] << ' ';
    for (int i = 1; i <= N * N; ++i) if (ans[i]) cout << i << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}