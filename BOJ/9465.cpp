#include <bits/stdc++.h>
using namespace std;

int n, cache[100000][3], cost[100000][2];

int matchCache(int N, int t) {
	if (N == 0 && t == 0) return 0;
	if (N == 0 && t == 1) return cost[0][0];
	if (N == 0 && t == 2) return cost[0][1];
	int& ret = cache[N][t];
	if (ret != -1) return ret;
	if (t == 0) ret = max({matchCache(N - 1, 0), matchCache(N - 1, 1), matchCache(N - 1, 2)});
	if (t == 1) ret = max(matchCache(N - 1, 0), matchCache(N - 1, 2)) + cost[N][0];
	if (t == 2) ret = max(matchCache(N - 1, 0), matchCache(N - 1, 1)) + cost[N][1];
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> n;
		memset(cache, -1, sizeof(cache));
		for (int j = 0; j < n; ++j) cin >> cost[j][0];
		for (int j = 0; j < n; ++j) cin >> cost[j][1];
		cout << max({matchCache(n - 1, 0), matchCache(n - 1, 1), matchCache(n - 1, 2)}) << "\n";
	}
}