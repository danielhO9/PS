#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;

LL matchCache(vector<vector<LL>>& cache, LL& k, LL f, LL r) {
	if (r == 0) return 1;
	LL& ret = cache[f][r];
	if (ret != -1) return ret;
	ret = 0;
	for (LL i = 0; i <= k - f - 1; ++i) {
		if (r < (f + 1) * (i + 1)) break;
		ret += matchCache(cache, k, i, r - (f + 1) * (i + 1));
		ret %= MOD;
	}
	return ret;
}

void solve() {
	LL n, k; cin >> n >> k;
	vector<vector<LL>> cache(k, vector<LL>(n + 1, -1));
	LL ans = 0;
	for (LL i = 0; i < k; ++i) {
		ans += matchCache(cache, k, i, n);
		ans %= MOD;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}