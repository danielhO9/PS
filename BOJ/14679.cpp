#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll pow (ll a, ll b, ll mod) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2, mod);
	half = (half * half) % mod;
	if (b % 2) return (half * a) % mod;
	else return half;
}

int N;
ll A, D, H;
ll MA, MD, MH;
ll Ap, Aa, Dp, Da, Hp, Ha;
ll apow[101], dpow[4], hpow[1001];

bool f() {
	ll pa = max(A - MD, 1ll);
	ll ma = max(MA - D, 1ll);
	return (MH + pa - 1) / pa <= (H + ma - 1) / ma;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	cin >> A >> D >> H;
	cin >> MA >> MD >> MH;
	cin >> Ap >> Aa >> Dp >> Da >> Hp >> Ha;
	for (ll i = 1; i <= 100; ++i) apow[i] = pow(i, Ap, 100);
	for (ll i = 1; i <= 3; ++i) dpow[i] = pow(i, Dp, 3);
	for (ll i = 1; i <= 1000; ++i) hpow[i] = pow(i, Hp, 1000);
	for (int i = 0; i < N; ++i) {
		if (!f()) {
			cout << -1;
			return 0;
		}
		A += MA;
		D += MD;
		H += MH;
		MA = (apow[MA] + Aa) % 100 + 1;
		MD = (dpow[MD] + Da) % 3 + 1;
		MH = (hpow[MH] + Ha) % 1000 + 1;
	}
	cout << A % MOD << ' ' << D % MOD << ' ' << H % MOD;
}