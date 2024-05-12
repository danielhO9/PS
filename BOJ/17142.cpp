#include <bits/stdc++.h>
using namespace std;

int N, M;
int lab[50][50];
vector<int> virus;
int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, 1, -1};
const int MAX = 987654321;
int ans = MAX;
vector<int> put;
int dis[50][50][10];
int fdis[50][50];

void query() {
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		if (lab[i][j] == 1 || lab[i][j] == 2) fdis[i][j] = 0;
		else fdis[i][j] = MAX;
	}
	for (auto i: put) {
		for (int j = 0; j < N; ++j) for (int k = 0; k < N; ++k) {
			fdis[j][k] = min(fdis[j][k], dis[j][k][i]);
		}
	}
	int tans = -1;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) tans = max(tans, fdis[i][j]);
	ans = min(ans, tans);
}

void generator() {
	if (put.size() == M) {
		query();
		return;
	}
	int s = put.empty() ? 0 : put.back() + 1;
	for (int i = s; i < virus.size(); ++i) {
		put.push_back(i);
		generator();
		put.pop_back();
	}
}

void bfs(int s) {
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) dis[i][j][s] = MAX;
	queue<int> Q; Q.push(virus[s]); dis[virus[s] / N][virus[s] % N][s] = 0;
	while (!Q.empty()) {
		int here = Q.front(); Q.pop();
		int y = here / N, x = here % N;
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i], nx = x + dx[i];
			if (0 <= ny && ny < N && 0 <= nx && nx < N && lab[ny][nx] != 1 && dis[ny][nx][s] == MAX) {
				dis[ny][nx][s] = dis[y][x][s] + 1;
				Q.push(ny * N + nx);
			}
		}
	}
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		cin >> lab[i][j];
		if (lab[i][j] == 2) virus.push_back(i * N + j);
	}
	for (int i = 0; i < virus.size(); ++i) bfs(i);
	generator();
	if (ans == MAX) cout << -1;
	else cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}