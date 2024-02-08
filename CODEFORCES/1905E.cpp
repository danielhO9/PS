#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL MOD = 998244353;
unordered_map<LL, pair<LL, LL>> M;
vector<LL> dpa(60);
vector<LL> dpb(60);

LL pow(LL a, LL b) {
	a %= MOD;
	if (b == 0) return 1LL;
	if (b == 1) return a;
	LL half = pow(a, b / 2);
	LL hpow = half * half; hpow %= MOD;
	if (b % 2 == 0) return hpow;
	return (hpow * a) % MOD;
}

void init() {
	M[1LL] = {1LL, 0LL};
	dpa[0] = 1LL;
	dpb[0] = 0LL;
	LL num = 1;
	for (LL i = 1; i < 60; ++i) {
		LL cnt = pow(2LL, i - 1);
		cnt = pow(2LL, cnt); --cnt;
		dpa[i] = (cnt * cnt) % MOD;
		dpa[i] += 4LL * dpa[i - 1]; dpa[i] %= MOD;
		dpb[i] = 2LL * dpb[i - 1] + dpa[i - 1]; dpb[i] %= MOD;
		num *= 2LL;
		M[num] = {dpa[i], dpb[i]};
	}
}

LL dfs(LL v, LL left, LL right) {
	LL dif = right - left + 1;
	auto ite = M.find(dif);
	if (ite != M.end()) {
		LL a = (ite->second).first;
		LL b = (ite->second).second;
		LL ret = a * (v % MOD) + b; ret %= MOD;
		// cout << v << ' ' << ret << '\n';
		return ret;
	}
	LL lcnt = (left + right) / 2 - left + 1;
	LL rcnt = right - (left + right) / 2;
	dfs(2LL * v, left, (left + right) / 2);
	dfs(2LL * v + 1LL, (left + right) / 2 + 1, right);
	LL a = ((pow(2LL, lcnt) - 1) * (pow(2LL, rcnt) - 1)) % MOD;
	a += 2LL * M[lcnt].first + 2LL * M[rcnt].first; a %= MOD;
	LL b = M[lcnt].second + M[rcnt].first + M[rcnt].second; b %= MOD;
	M[dif] = {a, b};
	LL ans = a * (v % MOD) + b; ans %= MOD;
	return ans;
}

void solve() {
	LL n; cin >> n;
	cout << dfs(1LL, 1LL, n) << '\n';
	// for (auto i: M) {
	// 	if (i.first < 7) cout << i.first << ' ' << i.second.first << ' ' << i.second.second << '\n';
	// }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	init();
	while (t--) solve();
}