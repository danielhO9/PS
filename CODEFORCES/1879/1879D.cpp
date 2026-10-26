#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;

void solve() {
	LL n; cin >> n;
	LL a[n + 1]; for (int i = 1; i <= n; ++i) cin >> a[i]; a[0] = 0;
	LL ans = 0, num = 0;
	vector<LL> osum(30), ocnt(30), zsum(30), zcnt(30);
	for (LL i = 0; i <= n; ++i) {
		num ^= a[i];
		for (int j = 0; j < 30; ++j) {
			LL temp = 0;
			if ((num | (1 << j)) == num) {
				temp = (zcnt[j] * i) % MOD;
				temp -= zsum[j]; temp += MOD; temp %= MOD;
				osum[j] += i; osum[j] %= MOD;
				++ocnt[j];
			} else {
				temp += (ocnt[j] * i) % MOD;
				temp -= osum[j]; temp += MOD; temp %= MOD;
				zsum[j] += i; zsum[j] %= MOD;
				++zcnt[j];
			}
			ans += temp * (1 << j); ans %= MOD;
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}