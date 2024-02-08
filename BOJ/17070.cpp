#include <bits/stdc++.h>
using namespace std;

int N, home[16][16], cache[16][16][3];

int matchCache(int y, int x, int t) {
	if (y < 0 || x < 0 || home[y][x]) return 0;
	if (t == 0 && (x - 1 < 0 || home[y][x - 1])) return 0;
	if (t == 1 && (y - 1 < 0 || home[y - 1][x])) return 0;
	if (t == 2 && (y - 1 < 0 || x - 1 < 0 || home[y - 1][x - 1] || home[y - 1][x] || home[y][x - 1])) return 0;
	if (y == 0 && x == 1) return 1;
	int& ret = cache[y][x][t];
	if (ret != -1) return ret;
	if (t == 0) ret = matchCache(y, x - 1, 0) + matchCache(y, x - 1, 2);
	else if (t == 1) ret = matchCache(y - 1, x, 1) + matchCache(y - 1, x, 2);
	else ret = matchCache(y - 1, x - 1, 0) + matchCache(y - 1, x - 1, 1) + matchCache(y - 1, x - 1, 2);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> home[i][j];
	memset(cache, -1, sizeof(cache));
	cout << matchCache(N - 1, N - 1, 0) + matchCache(N - 1, N - 1, 1) + matchCache(N - 1, N - 1, 2);
}