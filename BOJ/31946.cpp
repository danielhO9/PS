#include <bits/stdc++.h>
using namespace std;

int N, M, X;
int col[100][100];
bool vis[100][100];
int c;

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> col[i][j];
	cin >> X;
	queue<pair<int, int>> Q; Q.push({0, 0}); vis[0][0] = true; c = col[0][0];
	while (!Q.empty()) {
		auto [y, x] = Q.front(); Q.pop();
		for (int i = -X; i <= X; ++i) {
			int ai = abs(i);
			ai = X - ai;
			for (int j = -ai; j <= ai; ++j) {
				int ny = y + i, nx = x + j;
				if (0 <= ny && ny < N && 0 <= nx && nx < M && col[ny][nx] == c && !vis[ny][nx]) {
					Q.push({ny, nx});
					vis[ny][nx] = true;
				}
			}
			
		}
	}
	if (vis[N - 1][M - 1]) {
		cout << "ALIVE";
	} else cout << "DEAD";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}