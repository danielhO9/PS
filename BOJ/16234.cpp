#include <bits/stdc++.h>
using namespace std;

int N, L, R;
int ppl[50][50];
vector<int> adj[2500];
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, 1, -1};
bool vis[50][50];

bool query() {
	bool ret = false;
	for (int i = 0; i < N * N; ++i) adj[i].clear();
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		for (int k = 0; k < 4; ++k) {
			int ny = i + dy[k], nx = j + dx[k];
			if (0 <= ny && ny < N && 0 <= nx && nx < N && L <= abs(ppl[ny][nx] - ppl[i][j]) && abs(ppl[ny][nx] - ppl[i][j]) <= R) {
				adj[i * N + j].push_back(ny * N + nx);
			}
		}
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		if (vis[i][j]) continue;
		vector<int> tmp; tmp.push_back(i * N + j);
		queue<int> Q; Q.push(i * N + j); vis[i][j] = true;
		int sum = ppl[i][j];
		while (!Q.empty()) {
			int here = Q.front(); Q.pop();
			int y = here / N, x = here % N;
			for (auto there: adj[here]) {
				int ny = there / N, nx = there % N;
				if (!vis[ny][nx]) {
					Q.push(ny * N + nx); tmp.push_back(ny * N + nx);
					sum += ppl[ny][nx];
					vis[ny][nx] = true;
				}
			}
		}
		sum /= tmp.size();
		for (auto k: tmp) {
			int y = k / N, x = k % N;
			if (ppl[y][x] != sum) ret = true;
			ppl[y][x] = sum;
		}
	}
	return ret;
}

void solve() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> ppl[i][j];
	int ans = 0;
	while (query()) ++ans;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}