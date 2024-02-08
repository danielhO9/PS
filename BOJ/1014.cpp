#include <bits/stdc++.h>
using namespace std;
int N, M;

int matchCache(int r, int mask, vector<vector<int>>& cache, vector<vector<bool>>& blocked) {
	int& ret = cache[r][mask];
	if (ret != -1) return ret;
	for (int i = 0; i < M; ++i) if (mask == (mask | (1 << i))) {
		if (blocked[r][i]) {
			ret = INT32_MIN;
			return ret;
		}
	}
	vector<bool> available(M, 1);
	ret = 0;
	for (int i = 0; i < M; ++i) if (mask == (mask | (1 << i))) {
		++ret;
		if (i + 1 < M) {
			if (mask == (mask | (1 << (i + 1)))) {
				ret = INT32_MIN;
				return ret;
			}
			available[i + 1] = 0;
		}
		if (i - 1 >= 0) {
			if (mask == (mask | (1 << (i - 1)))) {
				ret = INT32_MIN;
				return ret;
			}
			available[i - 1] = 0;
		}
	}
	if (r == N - 1) return ret;
	int temp = INT32_MIN;
	for (int i = 0; i < (1 << M); ++i) {
		bool skip = false;
		for (int j = 0; j < M; ++j) if (!available[j] && i == (i | (1 << j))) { skip = true; break; }
		if (skip) continue;
		temp = max(temp, matchCache(r + 1, i, cache, blocked));
	}
	ret += temp;
	return ret;
}

void solve() {
	cin >> N >> M;
	vector<vector<bool>> blocked(N, vector<bool>(M, 0));
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		char c; cin >> c;
		if (c == 'x') blocked[i][j] = 1;
	}
	vector<vector<int>> cache(N, vector<int>(1 << M, -1));
	int ans = 0;
	for (int i = 0; i < (1 << M); ++i) ans = max(ans, matchCache(0, i, cache, blocked));
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}