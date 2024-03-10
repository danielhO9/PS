#include <bits/stdc++.h>
using namespace std;

int cache[20][1 << 20];
int N;
int D[20][20];

int matchCache(int x, int vis) {
	if (x == N) return 0;
	int& ret = cache[x][vis];
	if (ret != -1) return ret;
	ret = 987654321;
	for (int i = 0; i < N; ++i) if (!((vis >> i) & 1)) {
		ret = min(ret, matchCache(x + 1, vis ^ (1 << i)) + D[i][x]);
	}
	return ret;
}

void solve() {
	cin >> N; memset(cache, -1, sizeof(cache));
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> D[i][j];
	cout << matchCache(0, 0);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}