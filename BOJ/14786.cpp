#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

ld A, B, C;

double f(ld x) {
	return A * x + B * sin(x) - C;
}

ld fp(ld x) {
	return A + B * cos(x);
}

void solve() {
	cin >> A >> B >> C;
	// ld x = 0.0;
	// for (int i = 0; i < 1e3; ++i) {
	// 	ld nx = x - f(x) / fp(x);
	// 	x = nx;
	// }
	ld l = -2 * C, r = 2 * C;
	for (int i = 0; i < 1e6; ++i) {
		ld mid = (l + r) / 2;
		if (f(mid) > (ld) 0.0) r = mid;
		else l = mid;
	}
	cout << fixed;
	cout.precision(30);
	cout << l;
	// cout << '\n';
	// cout << f(l);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}