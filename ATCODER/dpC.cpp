#include <bits/stdc++.h>
using namespace std;

int cache[100000][3];
int c[100000][3];
int N;

int matchCache(int n, int t) {
	if (n == 0) return c[n][t];
	int& ret = cache[n][t];
	if (ret != -1) return ret;
	ret = INT32_MIN;
	for (int i = 0; i < 3; ++i) if (i != t) ret = max(ret, matchCache(n - 1, i) + c[n][t]);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> N;
	for (int i = 0; i < N; ++i) for (int j = 0; j < 3; ++j) cin >> c[i][j];
	
	cout << max({matchCache(N - 1, 0), matchCache(N - 1, 1), matchCache(N - 1, 2)});
}