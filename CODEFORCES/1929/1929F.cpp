#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;

void dfs(LL v, vector<LL>& V, vector<LL>& val, vector<LL>& L, vector<LL>& R) {
	if (L[v] != -1) dfs(L[v], V, val, L, R);
	V.push_back(val[v]);
	if (R[v] != -1) dfs(R[v], V, val, L, R);
}

LL pow(LL a, LL b) {
	if (b == 0) return 1;
	LL half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2 == 0) return half;
	return (half * a) % MOD;
}

LL com(LL a, LL b) {
	LL ret = 1, temp = 1;
	for (LL i = 1; i <= b; ++i) {
		ret *= a - b + i; ret %= MOD;
		temp *= i; temp %= MOD;
	}
	ret *= pow(temp, MOD - 2); ret %= MOD;
	return ret;
}

void solve() {
	LL n, C; cin >> n >> C;
	vector<LL> val(n + 1), L(n + 1), R(n + 1);
	for (LL i = 1; i <= n; ++i) cin >> L[i] >> R[i] >> val[i];
	vector<LL> V; V.push_back(1LL);
	dfs(1, V, val, L, R); V.push_back(C);
	LL ans = 1;
	LL l = -1, cnt = 0;
	for (auto i: V) {
		if (i == -1) ++cnt;
		else {
			if (cnt != 0) {
				ans *= com(cnt + i - l, cnt); ans %= MOD;
			}
			l = i; cnt = 0;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}