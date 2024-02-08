#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int M;
LL ans, MOD = 1000000007, N, S;

LL multiple(LL a, LL n) {
	if (n == 0) return 1;
	if (n == 1) return a;
	LL ret2 = multiple(a, n / 2);
	LL ret = ret2 * ret2; ret %= MOD;
	if (n % 2 == 1) ret *= a; ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> N >> S;
		ans += ((S * multiple(N, MOD - 2)) % MOD);
		ans %= MOD;
	}
	cout << ans;
}