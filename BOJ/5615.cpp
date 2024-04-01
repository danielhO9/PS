#include <bits/stdc++.h>
using namespace std;
typedef unsigned long ll;

ll pow(ll a, ll b, ll MOD) {
	a %= MOD;
	if (b == 0) return 1;
	ll half = pow(a, b / 2, MOD);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

bool millerRabin(ll n) {
	const ll a[3] = {2, 7, 61};
	for (int i = 0; i < 3; ++i) {
		if (a[i] == n) return true;
		ll k = n - 1;
		while (true) {
			ll temp = pow(a[i], k, n);
			if (temp == n - 1) break;
			if (k % 2 == 1) {
				if (temp == 1) break;
				else return false;
			}
			k /= 2;
		}
	}
	return true;
}

void solve() {
	int N; cin >> N; int cnt = 0;
	for (int i = 0; i < N; ++i) {
		ll n; cin >> n;
		if (millerRabin(2 * n + 1)) ++cnt;
	}
	cout << cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}