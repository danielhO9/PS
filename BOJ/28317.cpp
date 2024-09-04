#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e6 + 3;

int N, K;
int arr[1000000];
int mes[1000000];

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

ll fact(ll x) {
	if (x == 0) return 1ll;
	ll ret = 1ll;
	for (ll i = 1; i <= x; ++i) {
		ret *= i;
		ret %= MOD;
	}
	return ret;
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N - K + 1; ++i) cin >> arr[i];
	memset(mes, -1, sizeof(mes));
	for (int i = 0; i < N - K; ++i) {
		if (arr[i] == arr[i + 1] + 1) {
			if (mes[i % K] == 0) {
				cout << 0;
				return;
			}
			mes[i % K] = 0;
		} else if (arr[i] + 1 == arr[i + 1]) {
			if (mes[i % K] == 1) {
				cout << 0;
				return;
			}
			mes[i % K] = 1;
		} else if (arr[i] == arr[i + 1]) {
			continue;
		} else {
			cout << 0;
			return;
		}
	}
	ll n = 0, r = 0;
	for (int i = 0; i < K; ++i) {
		if (mes[i] == 1) ++r;
		if (mes[i] == -1) ++n;
	}
	r = arr[N - K] - r;
	ll ans = fact(n);
	// cout << n << ' ' << r << ' ';
	ans *= pow(fact(r), MOD - 2); ans %= MOD;
	ans *= pow(fact(n - r), MOD - 2); ans %= MOD;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
1---0---
*/