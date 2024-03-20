#include <bits/stdc++.h>
using namespace std;

int N, M;
int cache[1 << 14][14][14];
char tofu[14][14];
const int table[5][5] = {
	{10, 8, 7, 5, 1},
	{8, 6, 4, 3, 1},
	{7, 4, 3, 2, 1},
	{5, 3, 2, 2, 1},
	{1, 1, 1, 1, 0}
};

int calc(char& a, char& b) { return table[a - 'A'][b - 'A']; };

int matchCache(int mask, int i, int j) {
	if (i == N - 1 && j == M - 1) return 0;
	int& ret = cache[mask][i][j];
	if (ret != -1) return ret;
	int nxti, nxtj;
	if (j == M - 1) {
		nxti = i + 1; nxtj = 0;
	} else {
		nxti = i; nxtj = j + 1;
	}
	ret = matchCache(mask >> 1, nxti, nxtj);
	if (mask & 1) return ret;
	if (j != M - 1 && !((mask >> 1) & 1)) {
		ret = max(ret, calc(tofu[i][j], tofu[nxti][nxtj]) + matchCache((mask >> 1) | 1, nxti, nxtj));
	}
	if (i != N - 1) {
		ret = max(ret, calc(tofu[i][j], tofu[i + 1][j]) + matchCache((mask >> 1) | (1 << (M - 1)), nxti, nxtj));
	}
	return ret;
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		cin >> tofu[i][j];
		if (tofu[i][j] == 'F') tofu[i][j] = 'E';
	}
	memset(cache, -1, sizeof(cache));
	cout << matchCache(0, 0, 0);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}