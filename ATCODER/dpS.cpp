#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

string K;
int D;
ll cache[10000][100];

ll matchCache(int sz, int d) {
	if (sz == 0) {
		if (d == 0) return 1;
		else return 0;
	}
	ll& ret = cache[sz][d];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < 10; ++i) {
		ret += matchCache(sz - 1, (d - i + D) % D);
		ret %= MOD;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> K >> D;
	memset(cache, -1, sizeof(cache));
	int n = K.size();
	ll ans = 0;
	int past = 0;
	for (int i = 0; i < n; ++i) {
		int cur = K[i] - '0';
		for (int j = 0; j < (i + 1 == n ? cur + 1 : cur); ++j) {
			ans += matchCache(n - i - 1, (D - ((past + j) % D)) % D);
			ans %= MOD;
		}
		past += cur;
		past %= D;
		// cout << ans << '\n';
	}
	cout << (ans - 1 + MOD) % MOD;
}