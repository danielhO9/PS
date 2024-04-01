#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD[2] = {1031, 97};

ll cache[1031][1031][2];

ll matchCache(ll n, ll r, int t) {
	if (r == 0 || r == n) return 1;
	if (n < r) return 0;
	ll& ret = cache[n][r][t];
	if (ret != -1) return ret;
	ret = (matchCache(n - 1, r, t) + matchCache(n - 1, r - 1, t)) % MOD[t];
	return ret;
}

ll comb(ll n, ll r, ll t) {
	ll ret = 1;
	while (n != 0) {
        ret *= matchCache(n % MOD[t], r % MOD[t], t);
        ret %= MOD[t];
        n /= MOD[t]; r /= MOD[t];
    }
	return ret;
}

pair<ll, pair<ll, ll>> exEucild(ll a, ll b) {    // it returns {g, {x,y}}, ax+by=g
    if (b == 0) return {a, {1, 0}};
    pair<ll, pair<ll, ll>> ret = exEucild(b, a % b);
    ll g, x, y;
    g = ret.first;
    x = ret.second.first, y = ret.second.second;
    return {g, {y, x - (a / b) * y}};   
}

void solve() {
	ll N, M; cin >> N >> M;
	if (N < M - 1) {
		cout << 0 << '\n'; return;
	}
	if (M == 1 && N != 0) {
		cout << 0 << '\n'; return;
	}
	N -= M - 1;
	ll mod0 = comb(N + M - 2, N, 0); mod0 *= 659; mod0 %= 100007; mod0 *= MOD[1]; mod0 %= 100007;
	ll mod1 = comb(N + M - 2, N, 1); mod1 *= 35; mod1 %= 100007; mod1 *= MOD[0]; mod1 %= 100007;
	// cout << mod0 << ' ' << mod1 << ' ';
	ll ans = mod0 + mod1 ; ans %= 100007;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	int t; cin >> t;
	while (t--) solve();
}