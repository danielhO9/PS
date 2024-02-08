#include <bits/stdc++.h>
using namespace std;

int N, MOD = 10007, cache[52][52];

int matchCache(int n, int r) {
	if (r == 0 || n == r) return 1;
	int& ret = cache[n][r];
	if (ret != -1) return ret;
	ret = matchCache(n - 1, r) + matchCache(n - 1, r - 1);
	ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	memset(cache, -1, sizeof(cache));
	int ans = 0;
	for (int i = 1; i <= 13; ++i) {
		if (4 * i > N) break;
		if (i % 2 == 1) {
			ans += matchCache(52 - 4 * i, N - 4 * i) * matchCache(13, i);
			ans %= MOD;
		} else {
			ans -= matchCache(52 - 4 * i, N - 4 * i) * matchCache(13, i);
			while (ans < 0) ans += MOD;
			ans %= MOD;
		}
	}
	cout << ans;
}