#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
const int MAX_V = 20001;
int n, m, dy[4] = {1, 0, -1, 0}, dx[4] = {0, -1, 0, 1};
inline int cell(int y, int x) { return m * y + x; }

vector<int> adj[MAX_V];
map<int, int> capacity[MAX_V], flow[MAX_V];
vector<int> parent(MAX_V, -1);

int networkFlow(int source, int sink) {
	int totalFlow = 0;
	while (true) {
		for (int i = 0; i < MAX_V; ++i) parent[i] = -1;
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (auto there: adj[here]) {
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1) break;
		int amount = INF;
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

void solve() {
	cin >> n >> m;
	char city[n][m];
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> city[i][j];
	int k, h;
	for (int y = 0; y < n; ++y) for (int x = 0; x < m; ++x) {
		if (city[y][x] == '.') {
			adj[cell(y, x)].push_back(cell(y, x) + 10000);
			adj[cell(y, x) + 10000].push_back(cell(y, x));
			capacity[cell(y, x)][cell(y, x) + 10000] = 1;
			for (int i = 0; i < 4; ++i) {
				int ny = y + dy[i], nx = x + dx[i];
				int nc = cell(ny, nx);
				if (0 <= ny && ny < n && 0 <= nx && nx < m && city[ny][nx] != '#') {
					adj[cell(y, x) + 10000].push_back(cell(ny, nx));
					adj[cell(ny, nx)].push_back(cell(y, x) + 10000);
					capacity[cell(y, x) + 10000][cell(ny, nx)] = INF;
				}
			}
		} else if (city[y][x] == 'K' || city[y][x] == 'H') {
			if (city[y][x] == 'K') k = cell(y, x);
			if (city[y][x] == 'H') h = cell(y, x);
			for (int i = 0; i < 4; ++i) {
				int ny = y + dy[i], nx = x + dx[i];
				int nc = cell(ny, nx);
				if (0 <= ny && ny < n && 0 <= nx && nx < m && city[ny][nx] != '#') {
					adj[cell(y, x)].push_back(cell(ny, nx));
					adj[cell(ny, nx)].push_back(cell(y, x));
					capacity[cell(y, x)][cell(ny, nx)] = INF;
				}
			}
		}
	}
	auto ans = networkFlow(k, h);
	if (ans >= INF) {
		cout << -1; return;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}