#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000003;
ll cache[1001][1001];

ll comb(ll n, ll r) {
	if (r == 0 || r == n) return 1;
	ll& ret = cache[n][r];
	if (ret != -1) return ret;
	ret = comb(n - 1, r) + comb(n - 1, r - 1);
	ret %= MOD;
	return ret;
}

ll calc(ll n, ll r) {
	n -= 2 * r - 1;
	if (n < 0) return 0;
	return comb(n + r, r);
}

void solve() {
	ll N, K; cin >> N >> K;
	memset(cache, -1, sizeof(cache));
	ll ans = calc(N - 3, K - 1) * 2 + calc(N - 2, K);
	cout << ans % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}