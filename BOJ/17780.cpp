#include <bits/stdc++.h>
using namespace std;

int N, K;
int chess[12][12];
deque<int> tokens[12][12];
int r[10], c[10], w[10];
int dy[4] = {0, 0, -1, 1}, dx[4] = {1, -1, 0, 0};
bool done = false;

void query(int num, int t) {
	if (tokens[r[num]][c[num]].front() != num) return;
	int nr = r[num] + dy[w[num]], nc = c[num] + dx[w[num]];
	if (nr < 0 || nr >= N || nc < 0 || nc >= N || chess[nr][nc] == 2) {
		if (t == 1) return;
		w[num] = w[num] % 2 == 0 ? w[num] + 1 : w[num] - 1;
		query(num, 1);
	} else if (chess[nr][nc] == 0) {
		int tr = r[num], tc = c[num];
		while (!tokens[tr][tc].empty()) {
			int tmp = tokens[tr][tc].front(); tokens[tr][tc].pop_front();
			tokens[nr][nc].push_back(tmp);
			r[tmp] = nr; c[tmp] = nc;
		}
	} else {
		int tr = r[num], tc = c[num];
		while (!tokens[tr][tc].empty()) {
			int tmp = tokens[tr][tc].back(); tokens[tr][tc].pop_back();
			tokens[nr][nc].push_back(tmp);
			r[tmp] = nr; c[tmp] = nc;
		}
	}
	if (0 <= nr && nr < N && 0 <= nc && nc < N && tokens[nr][nc].size() >= 4) done = true;
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> chess[i][j];
	for (int i = 0; i < K; ++i) {
		int y, x, d; cin >> y >> x >> d; --y; --x; --d;
		tokens[y][x].push_back(i);
		r[i] = y, c[i] = x; w[i] = d;
	}
	int cnt = 0;
	while (cnt < 1001) {
		++cnt;
		for (int i = 0; i < K; ++i) {
			query(i, 0);
			if (done) break;
		}
		if (done) break;
	}
	if (cnt == 1001) cout << -1;
	else cout << cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}