#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef __float128 lf;

lf A, B, C;
ld a, b, c;

lf sin(lf x) {
    lf ret = x;
    lf p = 1.0;
    lf ope = 1.0;
    lf xpow = x;
    for (lf i = 3; i <= 60; i += 2.0) {
        p *= i; p *= (i - 1);
        ope *= -1;
        xpow *= x; xpow *= x;
        ret += xpow * ope / p;
    }
    return ret;
}

lf cos(lf x) {
    lf ret = 1.0;
    lf p = 1.0;
    lf ope = 1.0;
    lf xpow = 1.0;
    for (lf i = 2; i <= 60; i += 2.0) {
        p *= i; p *= (i - 1);
        ope *= -1;
        xpow *= x; xpow *= x;
        ret += xpow * ope / p;
    }
    return ret;
}

__float128 f(__float128 x) {
	return A * x + B * sin(x) - C;
}

__float128 fp(__float128 x) {
	return A + B * cos(x);
}

void solve() {
	cin >> a >> b >> c;
	A = a, B = b, C = c;
	__float128 x = 0.0;
	for (int i = 0; i < 1e5; ++i) {
		__float128 nx = x - f(x) / fp(x);
		x = nx;
	}
	cout << fixed;
	cout.precision(6);
	cout << (ld) x;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}