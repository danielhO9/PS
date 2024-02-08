#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL N, K;
const LL MOD = 1000000007;
LL cache[4000001];

LL power(LL a, LL b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	LL half = power(a, b / 2);
	LL ret = (half * half) % MOD;
	if (b % 2 == 0) return ret;
	ret *= a; ret %= MOD;
	return ret;
}

LL factorial(LL x) {
	if (x == 1) return 1;
	if (x == 0) return 1;
	LL& ret = cache[x];
	if (ret != -1) return ret;
	ret = x * factorial(x - 1);
	ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	int M; cin >> M;
	while (M--) {
		cin >> N >> K;
		LL ans = factorial(K) * factorial(N - K); ans %= MOD;
		LL temp = factorial(N);
		cout << (power(ans, MOD - 2) * temp) % MOD << '\n';
	}
}