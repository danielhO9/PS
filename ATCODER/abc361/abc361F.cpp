#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> tmp = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	ll half = pow(a, b/2);
	if (half > 1e9) return LLONG_MAX;
	if (b % 2 == 0) return (half * half);
	if (1e18/a < half * half) return LLONG_MAX;
	return (half * half * a);
}

void solve() {
	ll N; cin >> N;
	ll ans = 0;
	for (int i = 1; i < (1<<17); ++i) {
		ll num = 1;
		for (int j = 0; j < 17; ++j) if ((i >> j) & 1) {
			num *= tmp[j];
			num = min(num, 60ll);
		}
		ll ttmp = pow(N, 1.0/num);
		--ttmp;
		while (pow(ttmp + 1, num) <= N) ++ttmp;
		if (__builtin_popcount(i) % 2 == 0) ttmp = -ttmp;
		// if (num != 60) cout << num << ' ' << itm << '\n';
		ans += ttmp;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}