#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll S, T;

ll calc(ll a) {
	if (a == 1ll) return -1;
	if (a == 0ll) return 0;
	vector<ll> v;
	ll ret = 0ll;
	for (ll i = 1; i <= 1e7; ++i) {
		if (a / i < i) {
			v.push_back(i - 1);
			break;
		}
		if (a/i == i) {
			v.push_back(i);
			if (i % 2) ret -= a/i;
			else ret += a/i;
			break;
		}
		v.push_back(a/i);
		if (i % 2) ret -= a/i;
		else ret += a/i;
	}
	// for (auto i: v) cout << i << ' ';
	for (int i = 0; i < (int)v.size() - 1; ++i) {
		ll len = v[i] - v[i + 1];
		ll odd = len / 2, even = len / 2;
		if (len % 2) {
			if (v[i] % 2) ++odd;
			else ++even;
		}
		ret += (i + 1) * (even - odd);
	}
	return ret;
}

void solve() {
	cin >> S >> T;
	cout << calc(T) - calc(S - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
1 8
2 4
3 2
4 2
5 1
6 1
7 1
8 1
*/