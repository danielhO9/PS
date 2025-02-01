#include <bits/stdc++.h>
using namespace std;

int N;
int arr[1000][1000];
int cache[1000][1000][3];
int MIN = -987654321;

int matchCache(int i, int j, int t) {
	if (i == 0 && j == 0) return (t == 0 && arr[0][0] == t) ? 1 : MIN;
	int& ret = cache[i][j][t];
	if (ret != -1) return ret;
	ret = MIN;
	if (i != 0) ret = max(ret, matchCache(i - 1, j, t));
	if (j != 0) ret = max(ret, matchCache(i, j - 1, t));
	if (arr[i][j] == t) {
		if (i != 0) ret = max(ret, matchCache(i - 1, j, (t + 2) % 3) + 1);
		if (j != 0) ret = max(ret, matchCache(i, j - 1, (t + 2) % 3) + 1);
		if (t == 0) ret = max(ret, 1);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> arr[i][j];
	memset(cache, -1, sizeof(cache));
	int ans = 0;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) for (int t = 0; t < 3; ++t) {
		ans = max(ans, matchCache(i, j, t));
	}
	cout << ans;
}