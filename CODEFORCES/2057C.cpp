#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll l, r;

void solve() {
	cin >> l >> r;
	ll a = 0, b = 0, c = 0;
	int mx;
	for (int i = 29; i >= 0; --i) {
		if (c + (1 << i) > r) {
			continue;
		}
		if (b + (1 << i) - 1 < l) {
			b += (1 << i);
			c += (1 << i);
			continue;
		}
		b += (1 << i);
		mx = i;
		break;
	}
	for (int i = mx - 1; i >= 0; --i) {
		c += (1 << i);
	}
	if (l <= c - 1) a = c - 1;
	else a = b + 1;
	

	cout << a << ' ' << b << ' ' << c << '\n';
	assert(l <= a && a <= r);
	assert(l <= b && b <= r);
	assert(l <= c && c <= r);
	ll tmp = (a ^ b) + (b ^ c) + (c ^ a);
	// cout << tmp << '\n';
}

void solve2() {
	ll a, b, c;
	cin >> a >> b >> c;
	ll tmp = (a ^ b) + (b ^ c) + (c ^ a);
	cout << tmp << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}

/*
6
30
6
62
510
126
30
2147483646

6
30
6
62
30
126
30
2147483646

*/