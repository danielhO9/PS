#include <bits/stdc++.h>
using namespace std;

bool dragon[101][101];
int dy[4] = {0, -1, 0, 1};
int dx[4] = {1, 0, -1, 0};

void draw(int x, int y, int d, int g) {
	vector<pair<int, int>> V;
	V.push_back({y, x}); dragon[y][x] = true;
	V.push_back({y + dy[d], x + dx[d]}); dragon[y + dy[d]][x + dx[d]] = true;
	for (int i = 0; i < g; ++i) {
		pair<int, int> l = V.back(); int len = V.size();
		for (int j = len - 2; j >= 0; --j) {
			int ny = V[j].first - l.first, nx = V[j].second - l.second;
			V.push_back({l.first + nx, l.second - ny}); dragon[V.back().first][V.back().second] = true;
			// cout << V.back().first << ' ' << V.back().second << '\n';
		}
	}
}

void solve() {
	memset(dragon, 0, sizeof(dragon));
	int N; cin >> N;
	for (int i = 0; i < N; ++i) {
		int x, y, d, g; cin >> x >> y >> d >> g;
		draw(x, y, d, g);
	}
	int cnt = 0;
	for (int i = 0; i < 100; ++i) for (int j = 0; j < 100; ++j) {
		if (dragon[i][j] && dragon[i][j + 1] && dragon[i + 1][j] && dragon[i + 1][j + 1]) ++cnt;
	}
	cout << cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}