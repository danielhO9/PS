#include <bits/stdc++.h>
using namespace std;

int n, cache[500][500], ans, arr[500][500];

int matchCache(int i, int j) {
	if (i == 0) return arr[i][j];
	int& ret = cache[i][j];
	if (ret != -1) return ret;
	if (j - 1 >= 0) ret = max(ret, matchCache(i - 1, j - 1) + arr[i][j]);
	if (j < i) ret = max(ret, matchCache(i - 1, j) + arr[i][j]);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> n;
	for (int i = 0; i < n; ++i) for (int j = 0; j < i + 1; ++j) cin >> arr[i][j];
	for (int i = 0; i < n; ++i) ans = max(ans, matchCache(n - 1, i));
	cout << ans;
}