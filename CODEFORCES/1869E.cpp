#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD = 998244353;
ll powTemp[100001][121];
ll maxLen[100001][121];

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2); half %= MOD;
	half = half * half; half %= MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

void init() {
	memset(powTemp, 0, sizeof(powTemp));
	memset(maxLen, 0, sizeof(maxLen));
	for (ll i = 1; i <= 1e5; ++i) for (ll j = 0; j <= 120; ++j) {
		if (j == 0) powTemp[i][j] = 1;
		else powTemp[i][j] = (powTemp[i][j - 1] * i) % MOD;
	}
	for (ll i = 1; i <= 1e5; ++i) for (ll j = 1; j <= 120; ++j) {
		ll temp = powTemp[i][j] - powTemp[i - 1][j];
		while (temp < 0) temp += MOD;
		temp %= MOD;
		maxLen[i][j] = ((temp * i) % MOD) + maxLen[i - 1][j];
		maxLen[i][j] %= MOD;
	}
}

void solve() {
	ll n, m; cin >> n >> m;
	ll length[121];
	for (ll i = 1; i <= 120; ++i) {
		if (n < i) break;
		length[i] = maxLen[m][i] * pow(m, n - i);
		length[i] %= MOD;
	}
	ll ans = 0; ll size = 1, len = 0;
	while (size * 2ll <= n + 1) {
		size *= 2ll; ++len;
	}
	--size; --len;
	for (ll l = 0; l < 60; ++l) for (ll r = 0; r < 60; ++r) {
		ll maxL = max(l, r);
		maxL = len - maxL;
		if (maxL >= 0) {
			ll root = (1ll << (maxL + 1)) - 1; root %= MOD;
			ll L, R;
			if (l == 0) L = 1;
			else L = (1ll << (l - 1));
			if (r == 0) R = 1;
			else R = (1ll << (r - 1));
			L %= MOD; R %= MOD;
			root *= L; root %= MOD;
			root *= R; root %= MOD;
			root *= length[l + r + 1]; root %= MOD;
			ans += root; ans %= MOD;
		}
		ll rem = n - size;
		++maxL;
		if (rem > 0 && maxL >= 0) {
			if (r >= l) {
				ll avail = rem / (1ll << r);
				if (r > 0) avail *= (1ll << (r - 1));
				ll temp = rem % (1ll << r);
				if (r >= 1) temp -= (1ll << (r - 1)); temp = max(temp, 0ll);
				avail += temp; avail %= MOD;
				ll L;
				if (l == 0) L = 1;
				else L = 1ll << (l - 1);
				L %= MOD;
				avail *= L; avail %= MOD;
				avail *= length[l + r + 1]; avail %= MOD;
				ans += avail; ans %= MOD;
			} else {
				ll avail = rem / (1ll << l);
				if (l > 0) avail *= (1ll << (l - 1));
				ll temp = rem % (1ll << l);
				if (l > 0) temp = min(temp, 1ll << (l - 1));
				avail += temp; avail %= MOD;
				ll R;
				if (r == 0) R = 1;
				else R = 1ll << (r - 1);
				R %= MOD;
				avail *= R; avail %= MOD;
				avail *= length[l + r + 1]; avail %= MOD;
				ans += avail; ans %= MOD;
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}