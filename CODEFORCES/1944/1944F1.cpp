#include <bits/stdc++.h>
using namespace std;

int cache[401][401][401];
int sum[401][401][401];

void solve() {
	int n, k, p; cin >> n >> k >> p;
	for (int b = 0; b <= k; ++b) {
		cache[1][0][b] = 1;
		for (int a = 0; a <= k; ++a) sum[1][a][b] = 1;
	}
	for (int i = 2; i <= n; ++i) {
		for (int b = 0; b <= k; ++b) {
			for (int a = 0; a <= k; ++a) {
				int dif = max(0, a - b);
				cache[i][a][b] = sum[i - 1][k][a];
				if (dif > 0) cache[i][a][b] = (cache[i][a][b] + p - sum[i - 1][dif - 1][a]) % p;
			}
			sum[i][0][b] = cache[i][0][b];
			for (int a = 1; a <= k; ++a) sum[i][a][b] = (sum[i][a - 1][b] + cache[i][a][b]) % p;
		}
	}
	int ans = 0;
	for (int i = 0; i <= k; ++i) for (int j = i; j <= k; ++j) {
		ans = (ans + cache[n][j][i]) % p;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}