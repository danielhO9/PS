#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 30011;

ll inv_2;

void fwht_xor(vector<ll> &a, bool inv) {
    ll n = a.size();
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for(ll l = 0; l < n; l += s) {
            for(ll i = 0; i < h; i++) {
                ll t = a[l + h + i];
                a[l + h + i] = (a[l + i] - t + MOD) % MOD;
                a[l + i] += t;
                if(inv) a[l + h + i] = (a[l + h + i] * inv_2) % MOD, a[l + i] = (a[l + i] * inv_2) % MOD;
            }
        }
    }
}

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

ll N, K;

void solve() {
	cin >> N >> K;
	vector<ll> a(K + 1, 1);
	ll n = K + 1;
    ll i = 0;
    while ((1 << i) < (n << 1)) i++;
	n = 1 << i;
	a.resize(n);
	fwht_xor(a, false);
	for (int i = 0; i < a.size(); ++i) a[i] = pow(a[i], N);
	inv_2 = pow(2ll, MOD - 2);
	fwht_xor(a, true);
	ll ans = 0ll;
	for (int i = 1; i < a.size(); ++i) {
		ans += a[i];
		ans %= MOD;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}