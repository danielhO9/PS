#include <bits/stdc++.h>
using namespace std;

int N, M, K;
bool board[1000][1000];
int dist[1000][1000][11];
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, 1, -1};

void solve() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		char tmp; cin >> tmp;
		board[i][j] = (tmp == '1');
	}
	memset(dist, -1, sizeof(dist));
	queue<pair<pair<int, int>, int>> Q; Q.push({{0, 0}, 0});
	dist[0][0][0] = 1;
	while (!Q.empty()) {
		auto here = Q.front().first;
		int broked = Q.front().second;
		int d = dist[here.first][here.second][broked];
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			int ny = here.first + dy[i], nx = here.second + dx[i];
			if (!(0 <= ny && ny < N && 0 <= nx && nx < M)) continue;
			if (board[ny][nx]) {
				if (broked < K && dist[ny][nx][broked + 1] == -1) {
					Q.push({{ny, nx}, broked + 1});
					dist[ny][nx][broked + 1] = d + 1;
				}
			} else {
				if (dist[ny][nx][broked] == -1) {
					Q.push({{ny, nx}, broked});
					dist[ny][nx][broked] = d + 1;
				}
			}
		}
	}
	vector<int> tmp;
	for (int i = 0; i <= K; ++i) if (dist[N - 1][M - 1][i] >= 0) tmp.push_back(dist[N - 1][M - 1][i]);
	if (tmp.empty()) cout << -1;
	else cout << *min_element(tmp.begin(), tmp.end());
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}