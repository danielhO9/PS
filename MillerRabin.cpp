#include <bits/stdc++.h>
using namespace std;
typedef unsigned long ll;

const vector<vector<ll>> a = {
	{2, 7, 61},
	{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
};

ll pow(ll a, ll b, ll MOD) {
	a %= MOD;
	if (b == 0) return 1;
	ll half = pow(a, b / 2, MOD);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

bool millerRabin(ll n) {
	int type = 1;
	if (type == 1 && n < 40) {
		for (auto i: a[type]) if (i == n) return true;
		return false;
	}
	for (int i = 0; i < a[type].size(); ++i) {
		if (a[type][i] == n) return true;
		ll k = n - 1;
		while (true) {
			ll temp = pow(a[type][i], k, n);
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