#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;
LL cache[200001];

LL matchCache(LL x) {
	if (x == 0) return 1;
	if (x == 1) return 1;
	LL& ret = cache[x];
	if (ret != -1) return ret;
	ret = matchCache(x - 1);
	ret *= x;
	ret %= MOD;
	return ret;
}

void solve() {
	string s; cin >> s;
	int n = s.size();
	LL cnt = 0; char p;
	vector<LL> V;
	for (int i = 0; i < n; ++i) {
		if (i == 0) {
			p = s[i];
			++cnt;
		}
		else if (s[i] == p) {
			++cnt;
		} else {
			p = s[i];
			V.push_back(cnt);
			cnt = 1;
		}
	}
	V.push_back(cnt);
	LL l = 0;
	for (auto i: V) l += (i - 1); cout << l << ' ';
	LL ans = 1;
	for (auto i: V) {
		ans *= i; ans %= MOD;
	}
	ans *= matchCache(l); ans %= MOD;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	memset(cache, -1, sizeof(cache));
	while (t--) solve();
}