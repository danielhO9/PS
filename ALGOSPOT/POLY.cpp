#include <bits/stdc++.h>
using namespace std;

int MOD = 10000000, n, cache[101][101], ans;

int matchCache(int i, int j) {
	if (i == j) return 1;
	int& ret = cache[i][j];
	if (ret != -1) return ret;
	ret = 0;
	for (int k = 1; k <= i - j; ++k) {
		ret += matchCache(i - j, k) * (j + k - 1);
		ret %= MOD;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int C; cin >> C;
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < C; ++i) {
		cin >> n;
		ans = 0;
		for (int i = 1; i <= n; ++i) {
			ans += matchCache(n, i);
			ans %= MOD;
		}
		cout << ans << "\n";
	}
}